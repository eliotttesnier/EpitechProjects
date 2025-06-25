/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Kitchen
*/

#include <unistd.h>
#include <memory>
#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <queue>
#include <sstream>

#include "IngredientStock.hpp"
#include "Kitchen.hpp"
#include "../Pizza/Pizza.hpp"
#include "../Pizza/OrderData.hpp"
#include "../Utils/Logger.hpp"

/**
 * @brief Constructor for the Kitchen class
 *
 * @param config The parsed configuration object
 * @param id The unique identifier for this kitchen
 * @param processType Identifies if this kitchen is in parent or child process
 */
Kitchen::Kitchen(const Config &config, int id, ProcessType processType)
    : _config(config),
      _numCooks(config.getCooksPerKitchen()),
      _regenTimeMs(config.getRegenerationTimeMs()),
      _cookingMultiplier(config.getMultiplier()),
      _kitchenId(id),
      _isRunning(false),
      _currentLoad(0),
      _lastActivityTime(std::chrono::steady_clock::now()),
      _processType(processType),
      _hasReceivedFirstTask(false)
{
    _threadPool = std::make_unique<ThreadPool>(_numCooks);
    _ingredientStock = std::make_unique<IngredientStock>(_regenTimeMs);

    if (_processType != ProcessType::CHILD) {
        Logger::getInstance().logKitchenStatus(_kitchenId, "Kitchen created with " +
            std::to_string(_numCooks) + " cooks (multiplier: " +
            std::to_string(_cookingMultiplier) + ", regen time: " +
            std::to_string(_regenTimeMs) + "ms)");
    }
}

/**
 * @brief Destructor for the Kitchen class
 */
Kitchen::~Kitchen()
{
    try {
        if (_isRunning) {
            shutdown();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error during kitchen shutdown: " << e.what() << std::endl;
        Logger::getInstance().logKitchenStatus(_kitchenId,
            "Error during kitchen shutdown: " + std::string(e.what()));
    }
}

/**
 * @brief Initialize kitchen resources
 */
void Kitchen::initialize()
{
    _threadPool->initialize();
    _ingredientStock->initialize();
    _ingredientStock->startRegeneration();
    _isRunning = true;

    if (_processType != ProcessType::CHILD) {
        Logger::getInstance().logKitchenStatus(_kitchenId,
            "Kitchen initialized and ready to receive orders");
    }
}

/**
 * @brief Operate the kitchen (process orders, manage cooks, etc.)
 */
void Kitchen::operate()
{
    while (_isRunning) {
        bool tasksCompleted = false;
        {
            std::lock_guard<std::mutex> lock(_tasksMutex);
            size_t beforeSize = _activeTasks.size();
            _activeTasks.erase(
                std::remove_if(
                    _activeTasks.begin(),
                    _activeTasks.end(),
                    [](const std::future<bool> &f) {
                        return f.wait_for(std::chrono::milliseconds(0)) ==
                            std::future_status::ready;
                    }
                ),
                _activeTasks.end()
            );

            if (_activeTasks.size() < beforeSize)
                tasksCompleted = true;
        }

        if (tasksCompleted)
            updateLastActivity();

        if (_ipcChannel && _ipcChannel->hasData(100)) {
            std::string message = _ipcChannel->receive();
            if (!message.empty()) {
                if (message == "STATUS_REQUEST") {
                    std::string statusData = getStatusData();
                    _ipcChannel->send("STATUS_DATA:" + statusData);
                } else if (message.find("ORDER:") == 0) {
                    std::string data = message.substr(6);
                    size_t separatorPos = data.find(':');

                    if (separatorPos != std::string::npos) {
                        std::string orderIdStr = data.substr(0, separatorPos);
                        std::string packedPizzaData = data.substr(separatorPos + 1);

                        try {
                            int orderId = std::stoi(orderIdStr);
                            Pizza::Pizza pizza = Pizza::Pizza::unpack(packedPizzaData);
                            pizza.setOrderId(orderId);

                            addPizzaToQueue(pizza);
                            updateLastActivity();
                        } catch (const std::exception& e) {
                            std::cerr << "Kitchen " << _kitchenId << " child process error: "
                                << e.what() << std::endl;
                        }
                    }
                } else {
                    try {
                        Pizza::PizzaOrder order = Pizza::PizzaOrder::deserialize(message);

                        if (order.isValid) {
                            for (int i = 0; i < order.quantity; ++i) {
                                addPizzaToQueue(order.createPizza());
                            }
                            updateLastActivity();
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Kitchen " << _kitchenId << " error parsing message: "
                            << e.what() << std::endl;
                    }
                }
            }
        }

        {
            std::lock_guard<std::mutex> tasksLock(_tasksMutex);
            _currentLoad = _activeTasks.size() + getQueueSize();
        }

        auto pizzaOpt = getNextPizza();
        if (pizzaOpt.has_value()) {
            if (_ingredientStock->hasEnoughIngredients(pizzaOpt.value())) {
                _ingredientStock->consumeIngredients(pizzaOpt.value());

                try {
                    std::future<bool> result = _threadPool->addTask(
                        pizzaOpt.value(),
                        _cookingMultiplier,
                        [this](const Pizza::Pizza& pizza) {
                            this->notifyPizzaCooked(pizza);
                        }
                    );

                    {
                        std::lock_guard<std::mutex> lock(_tasksMutex);
                        _activeTasks.push_back(std::move(result));
                    }

                    updateLastActivity();
                } catch (const std::exception& e) {
                    std::cerr << "Kitchen "
                              << _kitchenId
                              << " error adding task to thread pool: "
                              << e.what() << std::endl;
                    Logger::getInstance().logKitchenStatus(_kitchenId,
                        "Error adding task to thread pool: " + std::string(e.what()));
                }
            } else if (pizzaOpt.has_value()) {
                addPizzaToQueue(pizzaOpt.value());
            }
        }

        bool noActiveWork = false;
        {
            std::lock_guard<std::mutex> lock(_tasksMutex);
            if (_activeTasks.empty() && getQueueSize() == 0) {
                noActiveWork = true;
            }
        }

        if (noActiveWork && isIdle()) {
            if (_processType != ProcessType::PARENT) {
                Logger::getInstance().logKitchenStatus(_kitchenId,
                    "Kitchen has been idle for over 5 seconds. Shutting down.");
            }
            sendShutdown();
            break;
        }

        {
            std::unique_lock<std::mutex> lock(_shutdownMutex);
            _shutdownCondVar.wait_for(lock, std::chrono::milliseconds(100), [this] {
                return !_isRunning;
            });
        }
    }
}

/**
 * @brief Shut down the kitchen safely
 */
void Kitchen::shutdown()
{
    if (!_isRunning)
        return;

    if (_processType != ProcessType::PARENT)
        Logger::getInstance().logKitchenStatus(_kitchenId, "Kitchen shutting down");

    {
        std::lock_guard<std::mutex> lock(_shutdownMutex);
        _isRunning = false;
    }
    _shutdownCondVar.notify_all();

    if (_ingredientStock) {
        _ingredientStock->stopRegeneration();
    }

    {
        std::lock_guard<std::mutex> lock(_tasksMutex);
        for (auto& task : _activeTasks) {
            if (task.valid()) {
                try {
                    auto status = task.wait_for(std::chrono::seconds(10));
                    if (status == std::future_status::timeout) {
                        std::cerr
                        << "Warning: Task didn't complete within timeout"
                        << std::endl;
                        Logger::getInstance().logKitchenStatus(_kitchenId,
                            "Warning: Task didn't complete within timeout");
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error waiting for task: " << e.what() << std::endl;
                    Logger::getInstance().logKitchenStatus(_kitchenId,
                        "Error waiting for task: " + std::string(e.what()));
                }
            }
        }
        _activeTasks.clear();
    }

    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        std::queue<Pizza::Pizza>().swap(_orderQueue);
    }
    _queueCondVar.notify_all();

    if (_threadPool) {
        try {
            _threadPool->shutdown();
            _threadPool.reset();
        } catch (const std::exception& e) {
            std::cerr << "Error shutting down thread pool: " << e.what() << std::endl;
            Logger::getInstance().logKitchenStatus(_kitchenId,
                "Error shutting down thread pool: " + std::string(e.what()));
        }
    }

    if (_ipcChannel) {
        try {
            if (_ipcChannel->isValid()) {
                _ipcChannel->send("SHUTDOWN");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            _ipcChannel->close();

            std::string parentToChildPath = "/tmp/reception_to_kitchen_"
                                            + std::to_string(_kitchenId) + ".fifo";
            std::string childToParentPath = "/tmp/kitchen_to_reception_"
                                            + std::to_string(_kitchenId) + ".fifo";
            unlink(parentToChildPath.c_str());
            unlink(childToParentPath.c_str());
        } catch (const std::exception& e) {
            std::cerr << "Error closing IPC channel: " << e.what() << std::endl;
            Logger::getInstance().logKitchenStatus(_kitchenId,
                "Error closing IPC channel: " + std::string(e.what()));
        }
    }
}

/**
 * @brief Send a shutdown message to the reception and terminate properly
 */
void Kitchen::sendShutdown()
{
    if (_ipcChannel && _ipcChannel->isValid()) {
        try {
            _ipcChannel->send("SHUTDOWN");
            Logger::getInstance().logKitchenStatus(_kitchenId,
                "Shutdown message sent to reception");
        } catch (const std::exception& e) {
            std::cerr << "Failed to send shutdown message: " << e.what() << std::endl;
        }
    }

    shutdown();
}

/**
 * @brief Check if kitchen is saturated (at max capacity)
 *
 * @return True if kitchen cannot accept more orders
 */
bool Kitchen::isSaturated() const
{
    int maxCapacity = getMaxCapacity();
    int currentLoad = getCurrentLoad();
    return currentLoad >= maxCapacity;
}

/**
 * @brief Check if kitchen has been idle for too long
 *
 * @return True if kitchen has been idle for more than 5s and has received at least one task
 */
bool Kitchen::isIdle() const
{
    if (!_hasReceivedFirstTask.load())
        return false;

    std::lock_guard<std::mutex> lock(_lastActivityMutex);
    auto now = std::chrono::steady_clock::now();
    auto timeSinceLastActivity =
        std::chrono::duration_cast<std::chrono::seconds>(now - _lastActivityTime);

    return timeSinceLastActivity.count() >= 5;
}

/**
 * @brief Get maximum pizza capacity of this kitchen
 *
 * @return Maximum capacity (2 * number of cooks)
 */
int Kitchen::getMaxCapacity() const
{
    return 2 * _numCooks;
}

/**
 * @brief Get current load (number of pizzas being processed or waiting)
 *
 * @return Current load
 */
int Kitchen::getCurrentLoad() const
{
    return _currentLoad;
}

/**
 * @brief Get the unique kitchen ID
 *
 * @return Kitchen ID
 */
int Kitchen::getKitchenId() const
{
    return _kitchenId;
}

/**
 * @brief Get current stock of ingredients
 *
 * @return Map of ingredient name to quantity
 */
std::unordered_map<std::string, int> Kitchen::getIngredientStock() const
{
    if (_ingredientStock) {
        return _ingredientStock->getStockLevels();
    }
    return {};
}

/**
 * @brief Check if this kitchen is still valid and can accept orders
 *
 * @return True if the kitchen is still valid
 */
bool Kitchen::isValid() const
{
    if (!_isRunning)
        return false;

    if (!_ipcChannel)
        return false;

    if (!_ipcChannel->isValid())
        return false;

    if (isSaturated())
        return false;

    try {
        _ipcChannel->hasData(0);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

/**
 * @brief Thread-safe method to add a pizza to the order queue
 *
 * @param pizza The pizza to add to the queue
 */
void Kitchen::addPizzaToQueue(const Pizza::Pizza& pizza)
{
    _hasReceivedFirstTask.store(true);

    size_t queueSize = 0;
    size_t activeTasksSize = 0;

    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _orderQueue.push(pizza);
        queueSize = _orderQueue.size();
        _queueCondVar.notify_one();
    }

    {
        std::lock_guard<std::mutex> tasksLock(_tasksMutex);
        activeTasksSize = _activeTasks.size();
    }

    _currentLoad = activeTasksSize + queueSize;
}

/**
 * @brief Thread-safe method to get the next pizza from the queue
 *
 * @return Optional pizza if available, empty optional otherwise
 */
std::optional<Pizza::Pizza> Kitchen::getNextPizza()
{
    std::lock_guard<std::mutex> lock(_queueMutex);
    if (!_orderQueue.empty()) {
        Pizza::Pizza pizza = _orderQueue.front();
        _orderQueue.pop();
        return pizza;
    }
    return std::nullopt;
}

/**
 * @brief Thread-safe method to get the current queue size
 *
 * @return Current number of pizzas in the queue
 */
size_t Kitchen::getQueueSize() const
{
    std::lock_guard<std::mutex> lock(_queueMutex);
    return _orderQueue.size();
}

/**
 * @brief Thread-safe method to update last activity time
 */
void Kitchen::updateLastActivity()
{
    std::lock_guard<std::mutex> lock(_lastActivityMutex);
    _lastActivityTime = std::chrono::steady_clock::now();
}

/**
 * @brief Get the number of busy cooks
 *
 * @return int Number of busy cooks
 */
int Kitchen::getBusyCooks() const
{
    return _threadPool ? _threadPool->getBusyWorkers() : 0;
}

/**
 * @brief Get the number of idle cooks
 *
 * @return int Number of idle cooks
 */
int Kitchen::getIdleCooks() const
{
    int totalCooks = _threadPool ? _threadPool->getTotalWorkers() : 0;
    int busyCooks = _threadPool ? _threadPool->getBusyWorkers() : 0;
    return totalCooks - busyCooks;
}

/**
 * @brief Get the total number of cooks
 *
 * @return int Total number of cooks
 */
int Kitchen::getTotalCooks() const
{
    return _threadPool ? _threadPool->getTotalWorkers() : 0;
}

/**
 * @brief Get a compact status data string
 *
 * Provides kitchen status data in a simple format:
 * "ID|BUSY_COOKS|IDLE_COOKS|TOTAL_COOKS|CURRENT_LOAD|MAX_CAPACITY|ING1:QTY1,ING2:QTY2,..."
 *
 * @return std::string Formatted status data string
 */
std::string Kitchen::getStatusData() const
{
    std::stringstream data;

    data << _kitchenId << "|";

    data << getBusyCooks() << "|";
    data << getIdleCooks() << "|";
    data << getTotalCooks() << "|";

    data << getCurrentLoad() << "|";
    data << getMaxCapacity() << "|";

    const auto& stock = getIngredientStock();
    bool firstIngredient = true;

    for (const auto& [ingredient, quantity] : stock) {
        if (!firstIngredient) {
            data << ",";
        }
        data << ingredient << ":" << quantity;
        firstIngredient = false;
    }

    return data.str();
}

/**
 * @brief Notify the reception that a pizza has been cooked
 *
 * @param pizza The cooked pizza
 */
void Kitchen::notifyPizzaCooked(const Pizza::Pizza& pizza)
{
    if (!_ipcChannel || !_ipcChannel->isValid()) {
        return;
    }

    try {
        std::string message = "PIZZA_COOKED:" + std::to_string(pizza.getOrderId()) +
        ":" + pizza.pack();

        _ipcChannel->send(message);
        updateLastActivity();
    } catch (const std::exception& e) {
        std::cerr << "Error sending pizza cooked notification: " << e.what() << std::endl;
    }
}
