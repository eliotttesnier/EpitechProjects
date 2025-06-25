/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** IngredientStock
*/

#include <chrono>
#include <string>
#include <unordered_map>

#include "IngredientStock.hpp"
#include "../Pizza/Pizza.hpp"
#include "../Pizza/PizzaConfig.hpp"

/**
 * @brief Constructor
 * @param regenerationTimeMs Time in milliseconds between regeneration cycles
 */
IngredientStock::IngredientStock(int regenerationTimeMs)
    : _regenerationTimeMs(regenerationTimeMs), _isRunning(false)
{
    initializeAllIngredients();
}

/**
 * @brief Destructor - stops regeneration thread
 */
IngredientStock::~IngredientStock()
{
    stopRegeneration();
}

/**
 * @brief Initialize stock with 5 units of each ingredient
 */
void IngredientStock::initialize()
{
    std::lock_guard<std::mutex> lock(_stockMutex);

    auto& config = Pizza::PizzaConfig::getInstance();
    auto ingredients = config.getAllIngredientIds();

    for (const auto& ingredient : ingredients) {
        _stock[ingredient] = 5;
    }
}

/**
 * @brief Start the automatic regeneration thread
 */
void IngredientStock::startRegeneration()
{
    if (_isRunning) {
        return;
    }

    _isRunning = true;
    _regenerationThread = std::thread(&IngredientStock::regenerationLoop, this);
}

/**
 * @brief Stop the automatic regeneration thread
 */
void IngredientStock::stopRegeneration()
{
    if (!_isRunning) {
        return;
    }

    _isRunning = false;
    _regenerationCV.notify_one();

    if (_regenerationThread.joinable()) {
        _regenerationThread.join();
    }
}

/**
 * @brief Check if we have enough ingredients for a pizza
 * @param pizza The pizza to check ingredients for
 * @return True if we have all required ingredients
 */
bool IngredientStock::hasEnoughIngredients(const Pizza::Pizza& pizza) const
{
    std::lock_guard<std::mutex> lock(_stockMutex);
    const auto& requiredIngredients = pizza.getIngredients();

    for (const auto& ingredient : requiredIngredients) {
        auto it = _stock.find(ingredient);
        if (it == _stock.end() || it->second <= 0) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Consume ingredients for a pizza
 * @param pizza The pizza to consume ingredients for
 * @return True if ingredients were successfully consumed
 */
bool IngredientStock::consumeIngredients(const Pizza::Pizza& pizza)
{
    std::lock_guard<std::mutex> lock(_stockMutex);
    const auto& requiredIngredients = pizza.getIngredients();

    for (const auto& ingredient : requiredIngredients) {
        auto it = _stock.find(ingredient);
        if (it == _stock.end() || it->second <= 0) {
            return false;
        }
    }

    for (const auto& ingredient : requiredIngredients) {
        _stock[ingredient]--;
    }

    return true;
}

/**
 * @brief Get current stock levels (thread-safe copy)
 * @return Map of ingredient name to quantity
 */
std::unordered_map<std::string, int> IngredientStock::getStockLevels() const
{
    std::lock_guard<std::mutex> lock(_stockMutex);
    return _stock;
}

/**
 * @brief Get stock level for a specific ingredient
 * @param ingredient The ingredient name
 * @return Current stock level
 */
int IngredientStock::getIngredientLevel(const std::string& ingredient) const
{
    std::lock_guard<std::mutex> lock(_stockMutex);
    auto it = _stock.find(ingredient);
    return (it != _stock.end()) ? it->second : 0;
}

/**
 * @brief Manually trigger regeneration (for testing purposes)
 */
void IngredientStock::forceRegeneration()
{
    regenerateIngredients();
}

/**
 * @brief Internal regeneration loop running in separate thread
 */
void IngredientStock::regenerationLoop()
{
    while (_isRunning) {
        std::unique_lock<std::mutex> lock(_regenerationMutex);

        auto status = _regenerationCV.wait_for(
            lock,
            std::chrono::milliseconds(_regenerationTimeMs)
        );

        if (!_isRunning) {
            break;
        }

        if (status == std::cv_status::timeout) {
            regenerateIngredients();
        }
    }
}

/**
 * @brief Regenerate 1 unit of each ingredient
 */
void IngredientStock::regenerateIngredients()
{
    std::lock_guard<std::mutex> lock(_stockMutex);

    auto& config = Pizza::PizzaConfig::getInstance();
    auto ingredients = config.getAllIngredientIds();

    for (const auto& ingredient : ingredients) {
        if (_stock[ingredient] >= 5)
            continue;
        _stock[ingredient]++;
    }
}

/**
 * @brief Initialize all known ingredients to 0
 */
void IngredientStock::initializeAllIngredients()
{
    std::lock_guard<std::mutex> lock(_stockMutex);

    auto& config = Pizza::PizzaConfig::getInstance();
    auto ingredients = config.getAllIngredientIds();

    for (const auto& ingredient : ingredients) {
        _stock[ingredient] = 0;
    }
}
