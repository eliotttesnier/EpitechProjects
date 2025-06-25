/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Reception
*/

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include <fstream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include "../Config/Config.hpp"
#include "../Kitchen/Kitchen.hpp"
#include "../Pizza/Pizza.hpp"
#include "../Pizza/OrderData.hpp"

class KitchenProcess;

class Reception {
    public:
        struct OrderTracker {
            int orderId;
            int totalPizzas;
            int completedPizzas;
            std::vector<Pizza::PizzaOrder> orders;
            time_t timestamp;

            OrderTracker() : orderId(0), totalPizzas(0), completedPizzas(0), timestamp(0) {}

            bool isComplete() const {
                return completedPizzas >= totalPizzas;
            }

            std::string getDescription() const {
                std::string desc = "Order #" + std::to_string(orderId) + ": ";
                for (size_t i = 0; i < orders.size(); ++i) {
                    desc += orders[i].getDescription();
                    if (i < orders.size() - 1) desc += ", ";
                }
                return desc;
            }

            std::string getElapsedTime() const {
                if (timestamp == 0) return "N/A";
                time_t now = std::time(nullptr);
                int elapsed = static_cast<int>(now - timestamp);
                int minutes = elapsed / 60;
                int seconds = elapsed % 60;
                return std::to_string(minutes) + "m " + std::to_string(seconds) + "s";
            }
        };

        Reception(const Config &config);
        ~Reception();

        void run();
        void stop();

        void processCommand(const std::string& command);
        void processOrderCommand(const std::string& command);
        void displayHelp() const;

        void createNewKitchen();
        void showStatus() const;

        void startListenerThread();
        void stopListenerThread();

    protected:
        void displayWelcomeMessage() const;

        std::vector<std::string> splitOrderString(const std::string& orderString) const;
        Pizza::PizzaOrder parsePizzaOrder(const std::string& orderItem) const;
        std::string stringToPizzaId(const std::string& typeStr) const;
        Pizza::PizzaSize stringToPizzaSize(const std::string& sizeStr) const;
        bool parseQuantity(const std::string& quantityStr, int& quantity) const;

    protected:
        void displayKitchenHeader() const;
        void displayKitchenWithRemoteData(const std::string& statusData) const;
        bool requestKitchenStatus(const std::shared_ptr<Kitchen>& kitchen, std::string& statusData) const;

    private:
        void checkKitchenMessages();
        void checkKitchenConnections() const;
        void monitorKitchenProcesses();
        bool isNewKitchenNeeded() const;
        std::shared_ptr<Kitchen> findAvailableKitchen();
        std::shared_ptr<Kitchen> findLeastLoadedKitchen();
        int calculateRequiredKitchens(int totalPizzaCount) const;
        void createNecessaryKitchens(int requiredCount);
        void increaseKitchenLoad(int kitchenId);
        void decreaseKitchenLoad(int kitchenId);
        int getEstimatedKitchenLoad(int kitchenId) const;

        std::pair<Pizza::OrderBatch, int> validateAndParseOrders(const std::string& command, bool& hasValidOrders, bool& hasInvalidOrders);
        void cleanupInvalidKitchens();
        bool assignPizzaToKitchen(const Pizza::PizzaOrder& order);
        bool assignPizzaToSpecificKitchen(const Pizza::PizzaOrder& order, std::shared_ptr<Kitchen>& kitchen);
        bool createKitchenAndAssignPizza(const Pizza::PizzaOrder& order);

        void listenerThreadFunction();

        int createNewOrder(const std::vector<Pizza::PizzaOrder>& orders);
        void handlePizzaCooked(int orderId, const Pizza::PizzaOrder& pizza, int kitchenId);
        void checkCompletedOrders();
        void processPizzaCookedMessage(const std::string& message, int kitchenId);

        Config _config;
        std::vector<std::shared_ptr<Kitchen>> _kitchens;
        std::vector<std::shared_ptr<KitchenProcess>> _kitchenProcesses;
        mutable std::mutex _kitchensMutex;
        std::unordered_map<int, int> _kitchenLoads;
        mutable std::mutex _loadsMutex;
        bool _running;
        std::ofstream _logFile;

        std::thread _listenerThread;
        std::atomic<bool> _listenerRunning;
        std::condition_variable _listenerCondVar;
        std::mutex _listenerMutex;

        std::unordered_map<int, OrderTracker> _orderTrackers;
        mutable std::mutex _ordersMutex;
        int _nextOrderId;
};
