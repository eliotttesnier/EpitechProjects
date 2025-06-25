/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** ThreadPool
*/

#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <future>
#include <memory>

#include "../Pizza/Pizza.hpp"
#include "Cook.hpp"

class ThreadPool {
    public:
        ThreadPool(int numThreads);
        ~ThreadPool();

        void initialize();
        std::future<bool> addTask(const Pizza::Pizza& pizza, float cookingMultiplier,
                                 std::function<void(const Pizza::Pizza&)> onPizzaCooked = nullptr);
        void shutdown();

        int getBusyWorkers() const;
        int getTotalWorkers() const;
        int getAvailableCooks() const;

    private:
        int _numThreads;
        std::vector<std::thread> _threads;
        std::queue<std::function<void()>> _taskQueue;
        mutable std::mutex _queueMutex;
        std::condition_variable _queueCondVar;
        std::atomic<bool> _isRunning;
        std::atomic<int> _busyWorkers;
        std::vector<std::unique_ptr<Cook>> _cooks;
        mutable std::mutex _cooksMutex;

        void workerFunction();
};
