/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"

#include <iostream>
#include <functional>
#include <thread>
#include <utility>
#include <memory>

#include "Cook.hpp"

/**
 * @brief Constructor for the ThreadPool class
 *
 * @param numThreads Number of worker threads to create
 */
ThreadPool::ThreadPool(int numThreads) :
    _numThreads(numThreads),
    _isRunning(false),
    _busyWorkers(0)
{
    if (_numThreads <= 0)
        _numThreads = 1;
}

/**
 * @brief Destructor for the ThreadPool class
 */
ThreadPool::~ThreadPool()
{
    if (_isRunning)
        shutdown();
}

/**
 * @brief Initialize and start the thread pool
 */
void ThreadPool::initialize()
{
    if (_isRunning)
        return;

    _isRunning = true;

    for (int i = 0; i < _numThreads; ++i) {
        _cooks.push_back(std::make_unique<Cook>(i + 1));
    }

    _threads.reserve(_numThreads);
    for (int i = 0; i < _numThreads; ++i) {
        _threads.emplace_back(&ThreadPool::workerFunction, this);
    }
}

/**
 * @brief Add a new task to the queue
 *
 * @param pizza The pizza to process
 * @param cookingMultiplier The cooking time multiplier
 * @param onPizzaCooked Callback function called when pizza is cooked
 *
 * @return A future that will contain the result of the pizza cooking process
 */
std::future<bool> ThreadPool::addTask(const Pizza::Pizza& pizza, float cookingMultiplier,
                                     std::function<void(const Pizza::Pizza&)> onPizzaCooked)
{
    auto taskPtr = std::make_shared<std::packaged_task<bool()>>(
        [this, pizza, cookingMultiplier, onPizzaCooked]() {
            try {
                std::unique_lock<std::mutex> lock(this->_cooksMutex);

                for (auto& cook : this->_cooks) {
                    if (!cook->isBusy()) {
                        lock.unlock();
                        bool result = cook->cookPizza(pizza, cookingMultiplier).get();

                        if (result && onPizzaCooked)
                            onPizzaCooked(pizza);

                        return result;
                    }
                }
                lock.unlock();

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                throw std::runtime_error("No available cook found");
            } catch (const std::exception& e) {
                std::cerr << "Error assigning pizza to cook: " << e.what() << std::endl;
                return false;
            }
        }
    );

    std::future<bool> result = taskPtr->get_future();
    {
        std::unique_lock<std::mutex> lock(_queueMutex);

        if (!_isRunning)
            throw std::runtime_error("Cannot add task to stopped ThreadPool");

        _taskQueue.emplace([taskPtr]() {
            (*taskPtr)();
        });
    }

    _queueCondVar.notify_one();
    return result;
}

/**
 * @brief Shutdown the thread pool gracefully
 */
void ThreadPool::shutdown()
{
    {
        std::unique_lock<std::mutex> lock(_queueMutex);
        _isRunning = false;
    }

    _queueCondVar.notify_all();

    for (auto& thread : _threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    _threads.clear();
}

/**
 * @brief Get current number of busy workers
 *
 * @return Number of busy workers
 */
int ThreadPool::getBusyWorkers() const
{
    return _busyWorkers;
}

/**
 * @brief Get total number of worker threads
 *
 * @return Total number of worker threads
 */
int ThreadPool::getTotalWorkers() const
{
    return _numThreads;
}

/**
 * @brief Get number of available (non-busy) cooks
 *
 * @return Number of available cooks
 */
int ThreadPool::getAvailableCooks() const
{
    std::lock_guard<std::mutex> lock(_cooksMutex);
    int available = 0;
    for (const auto& cook : _cooks) {
        if (!cook->isBusy()) {
            available++;
        }
    }
    return available;
}

/**
 * @brief Worker thread function
 */
void ThreadPool::workerFunction()
{
    while (_isRunning) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(_queueMutex);

            _queueCondVar.wait(lock, [this]() {
                return !_taskQueue.empty() || !_isRunning;
            });

            if (!_isRunning && _taskQueue.empty()) {
                return;
            }

            if (!_taskQueue.empty()) {
                task = std::move(_taskQueue.front());
                _taskQueue.pop();
            }
        }

        if (task) {
            _busyWorkers++;

            try {
                task();
            } catch (const std::exception& e) {
                std::cerr << "Exception in worker thread: " << e.what() << std::endl;
            }

            _busyWorkers--;
        }
    }
}
