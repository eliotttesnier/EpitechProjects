/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Kitchen
*/

#pragma once

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <future>
#include <optional>

#include "../Config/Config.hpp"
#include "../Pizza/Pizza.hpp"
#include "../IPC/IIPCChannel.hpp"
#include "ThreadPool.hpp"
#include "IngredientStock.hpp"

class Kitchen {
    public:
        enum class ProcessType {
            PARENT,
            CHILD,
            UNDEFINED
        };

        Kitchen(const Config &config, int id, ProcessType processType = ProcessType::UNDEFINED);
        ~Kitchen();

        void initialize();
        void operate();
        void shutdown();
        void sendShutdown();
        bool isSaturated() const;
        bool isIdle() const;
        bool isValid() const;

        int getMaxCapacity() const;
        int getCurrentLoad() const;
        int getKitchenId() const;
        std::shared_ptr<Plazza::IIPCChannel> getIpcChannel() const { return _ipcChannel; }
        void setIpcChannel(std::shared_ptr<Plazza::IIPCChannel> channel) { _ipcChannel = channel; }
        std::unordered_map<std::string, int> getIngredientStock() const;

        int getBusyCooks() const;
        int getIdleCooks() const;
        int getTotalCooks() const;
        std::string getStatusData() const;

        void addPizzaToQueue(const Pizza::Pizza& pizza);
        std::optional<Pizza::Pizza> getNextPizza();
        size_t getQueueSize() const;
        void updateLastActivity();
        void notifyPizzaCooked(const Pizza::Pizza& pizza);

    protected:
    private:
        Config _config;
        int _numCooks;
        int _regenTimeMs;
        float _cookingMultiplier;
        int _kitchenId;

        std::queue<Pizza::Pizza> _orderQueue;
        mutable std::mutex _queueMutex;
        std::condition_variable _queueCondVar;
        std::atomic<bool> _isRunning;
        std::atomic<int> _currentLoad;
        std::chrono::time_point<std::chrono::steady_clock> _lastActivityTime;
        mutable std::mutex _lastActivityMutex;

        mutable std::mutex _tasksMutex;
        std::condition_variable _shutdownCondVar;
        mutable std::mutex _shutdownMutex;

        std::unique_ptr<IngredientStock> _ingredientStock;

        std::unique_ptr<ThreadPool> _threadPool;
        std::vector<std::future<bool>> _activeTasks;

        std::shared_ptr<Plazza::IIPCChannel> _ipcChannel;
        ProcessType _processType;
        std::atomic<bool> _hasReceivedFirstTask;
};
