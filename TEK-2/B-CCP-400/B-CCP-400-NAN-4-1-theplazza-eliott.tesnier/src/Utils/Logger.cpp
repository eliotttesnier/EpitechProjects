/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Logger
*/

#include <iostream>
#include <ctime>
#include <string>

#include "Logger.hpp"
#include "../Utils/ColorUtils.hpp"

Logger& Logger::getInstance(const std::string& filename)
{
    static Logger instance(filename);
    return instance;
}

Logger::Logger(const std::string& filename)
    : _filename(filename)
{
    _logFile.open(_filename, std::ios::out | std::ios::trunc);

    if (!_logFile.is_open()) {
        std::cerr << ColorUtils::RED << "Error: Could not open log file: "
                  << _filename << ColorUtils::RESET << std::endl;
        return;
    }

    std::string header = "==========================================\n"
                         "     PLAZZA LOG - SESSION STARTED\n"
                         "     " + getTimestamp() + "\n"
                         "==========================================\n";

    _logFile << header << std::endl;
}

Logger::~Logger()
{
    if (_logFile.is_open()) {
        std::string footer = "\n==========================================\n"
                            "     PLAZZA LOG - SESSION ENDED\n"
                            "     " + getTimestamp() + "\n"
                            "==========================================\n";

        _logFile << footer << std::endl;
        _logFile.close();
    }
}

void Logger::log(LogLevel level, const std::string& message)
{
    std::stringstream ss;
    ss << "[" << getTimestamp() << "] "
       << "[" << logLevelToString(level) << "] "
       << message;

    writeToLog(ss.str());
}

void Logger::logOrder(const Pizza::PizzaOrder& order,
    OrderStatus status, int kitchenId, int orderId)
{
    if (!order.isValid) {
        log(LogLevel::WARNING, "Attempted to log invalid pizza order");
        return;
    }

    std::stringstream ss;
    ss << "[" << getTimestamp() << "] "
       << "[ORDER";

    if (orderId >= 0)
        ss << " #" << orderId;

    ss << "] ";

    if (kitchenId >= 0)
        ss << "Kitchen #" << kitchenId << " - ";

    ss << "Status: " << orderStatusToString(status) << " - "
       << order.getDescription();

    writeToLog(ss.str());
}

void Logger::logOrderBatch(const Pizza::OrderBatch& batch, OrderStatus status)
{
    log(LogLevel::INFO, "Processing order batch with " +
        std::to_string(batch.validCount()) + " valid orders");

    for (const auto& order : batch.orders) {
        if (order.isValid) {
            logOrder(order, status);
        }
    }
}

void Logger::logKitchenStatus(int kitchenId, const std::string& message)
{
    std::stringstream ss;
    ss << "[" << getTimestamp() << "] "
       << "[KITCHEN #" << kitchenId << "] "
       << message;

    writeToLog(ss.str());
}

std::string Logger::getTimestamp() const
{
    auto now = std::chrono::system_clock::now();
    auto nowTime = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::stringstream ss;
    std::tm tm_buf{};
    localtime_r(&nowTime, &tm_buf);

    ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return ss.str();
}

std::string Logger::orderStatusToString(OrderStatus status)
{
    switch (status) {
        case OrderStatus::PLACED:      return "PLACED";
        case OrderStatus::ASSIGNED:    return "ASSIGNED";
        case OrderStatus::IN_PROGRESS: return "IN_PROGRESS";
        case OrderStatus::COMPLETED:   return "COMPLETED";
        case OrderStatus::FAILED:      return "FAILED";
        default:                       return "UNKNOWN";
    }
}

std::string Logger::logLevelToString(LogLevel level)
{
    switch (level) {
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::DEBUG:   return "DEBUG";
        default:                return "UNKNOWN";
    }
}

void Logger::writeToLog(const std::string& message)
{
    std::lock_guard<std::mutex> lock(_logMutex);

    if (_logFile.is_open()) {
        _logFile << message << std::endl;
        _logFile.flush();
    } else {
        std::cerr << ColorUtils::YELLOW << "Warning: Attempted to write to closed log file"
                  << ColorUtils::RESET << std::endl;
    }
}
