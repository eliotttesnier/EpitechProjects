/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Cook
*/

#include "Cook.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <algorithm>
#include <string>

#include "../Utils/Logger.hpp"

/**
 * @brief Constructor for the Cook class
 *
 * @param id Unique identifier for the cook
 */
Cook::Cook(int id) :
    _id(id),
    _isBusy(false),
    _totalPizzasCooked(0),
    _shouldCancel(false)
{
}

/**
 * @brief Destructor for the Cook class
 */
Cook::~Cook()
{
}

/**
 * @brief Start cooking a pizza and return a future to check when it's done
 *
 * @param pizza The pizza to cook
 * @param cookingMultiplier The multiplier for cooking time
 * @return std::future<bool> Future that resolves to true when cooking is complete
 */
std::future<bool> Cook::cookPizza(const Pizza::Pizza& pizza, float cookingMultiplier)
{
    {
        std::lock_guard<std::mutex> lock(_stateMutex);
        if (_isBusy.load()) {
            throw std::runtime_error("Cook is already busy");
        }
        _isBusy.store(true);
        _shouldCancel.store(false);
    }

    auto taskPtr = std::make_shared<std::packaged_task<bool()>>(
        [this, pizza, cookingMultiplier]() {
            return this->performCooking(pizza, cookingMultiplier);
        }
    );

    std::future<bool> result = taskPtr->get_future();

    std::thread([taskPtr]() {
        (*taskPtr)();
    }).detach();

    return result;
}

/**
 * @brief Check if the cook is currently busy
 *
 * @return true if the cook is busy, false otherwise
 */
bool Cook::isBusy() const
{
    return _isBusy.load();
}

/**
 * @brief Get the cook's ID
 *
 * @return The cook's ID
 */
int Cook::getId() const
{
    return _id;
}

/**
 * @brief Get the total number of pizzas cooked by this cook
 *
 * @return Number of pizzas cooked
 */
int Cook::getTotalPizzasCooked() const
{
    return _totalPizzasCooked.load();
}

/**
 * @brief Perform the actual cooking of the pizza
 *
 * @param pizza The pizza to cook
 * @param cookingMultiplier The multiplier for cooking time
 * @return true if cooking was successful, false otherwise
 */
bool Cook::performCooking(const Pizza::Pizza& pizza, float cookingMultiplier)
{
    try {
        float cookingTime = pizza.getActualCookingTime(cookingMultiplier);
        int cookingTimeMs = static_cast<int>(cookingTime * 1000);

        auto startTime = std::chrono::steady_clock::now();

        const int checkInterval = 100;
        int elapsed = 0;

        while (elapsed < cookingTimeMs && !_shouldCancel.load()) {
            int sleepTime = std::min(checkInterval, cookingTimeMs - elapsed);
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            elapsed += sleepTime;
        }

        if (_shouldCancel.load()) {
            std::lock_guard<std::mutex> lock(_stateMutex);
            _isBusy.store(false);

            return false;
        }

        auto endTime = std::chrono::steady_clock::now();
        auto actualDuration =
            std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        std::stringstream ss;
        ss << std::fixed << std::setprecision(3) << (actualDuration.count() / 1000.0);
        std::string actualTimeStr = ss.str();

        {
            std::lock_guard<std::mutex> lock(_stateMutex);
            _totalPizzasCooked++;
            _isBusy.store(false);
        }

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Cook #" << _id << ": Error cooking pizza: " << e.what() << std::endl;

        Logger::getInstance().log(
            Logger::LogLevel::ERROR,
            "Cook #" + std::to_string(_id) + ": Error cooking pizza: " + e.what()
        );

        std::lock_guard<std::mutex> lock(_stateMutex);
        _isBusy.store(false);
        return false;
    }
}

/**
 * @brief Cancel the current cooking task
 */
void Cook::cancelCurrentTask()
{
    _shouldCancel.store(true);
}
