/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** IngredientStock
*/

#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>

namespace Pizza {
    class Pizza;
}

class IngredientStock {
    public:
        explicit IngredientStock(int regenerationTimeMs);
        ~IngredientStock();

        void initialize();
        void startRegeneration();
        void stopRegeneration();
        bool hasEnoughIngredients(const Pizza::Pizza& pizza) const;
        bool consumeIngredients(const Pizza::Pizza& pizza);
        std::unordered_map<std::string, int> getStockLevels() const;
        int getIngredientLevel(const std::string& ingredient) const;
        void forceRegeneration();

    private:
        void regenerationLoop();
        void regenerateIngredients();
        void initializeAllIngredients();

        int _regenerationTimeMs;

        std::unordered_map<std::string, int> _stock;
        mutable std::mutex _stockMutex;

        std::thread _regenerationThread;
        std::atomic<bool> _isRunning;
        std::condition_variable _regenerationCV;
        std::mutex _regenerationMutex;
};
