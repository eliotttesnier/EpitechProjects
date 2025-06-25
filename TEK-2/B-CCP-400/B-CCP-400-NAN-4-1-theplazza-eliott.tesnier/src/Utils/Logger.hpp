/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Logger
*/

#pragma once

#include <fstream>
#include <string>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <sstream>
#include <memory>

#include "../Pizza/Pizza.hpp"
#include "../Pizza/OrderData.hpp"

class Logger {
    public:
        enum class LogLevel {
            INFO,
            WARNING,
            ERROR,
            DEBUG
        };

        enum class OrderStatus {
            PLACED,
            ASSIGNED,
            IN_PROGRESS,
            COMPLETED,
            FAILED
        };

        static Logger& getInstance(const std::string& filename = "plazza.log");

        ~Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        void log(LogLevel level, const std::string& message);
        void logOrder(const Pizza::PizzaOrder& order, OrderStatus status, int kitchenId = -1, int orderId = -1);
        void logOrderBatch(const Pizza::OrderBatch& batch, OrderStatus status);
        void logKitchenStatus(int kitchenId, const std::string& message);

        static std::string orderStatusToString(OrderStatus status);
        static std::string logLevelToString(LogLevel level);

    private:
        explicit Logger(const std::string& filename);

        std::string getTimestamp() const;
        void writeToLog(const std::string& message);

        std::ofstream _logFile;
        std::string _filename;
        mutable std::mutex _logMutex;
};
