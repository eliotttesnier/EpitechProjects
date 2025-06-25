/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Pizza
*/

#include "Pizza.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>

namespace Pizza {

/**
 * @brief Constructor using pizza ID (modern approach)
 */
Pizza::Pizza(const std::string& pizzaId, PizzaSize size, int orderId)
    : _pizzaId(pizzaId), _size(size), _orderId(orderId), _baseCookingTime(0)
{
    _initializeFromConfig();
}

/**
 * @brief Constructor using pizza name (legacy compatibility)
 */
Pizza::Pizza(const std::string& pizzaName, const std::string& sizeStr, int orderId)
    : _size(PizzaConfig::stringToSize(sizeStr)), _orderId(orderId), _baseCookingTime(0)
{
    auto& config = PizzaConfig::getInstance();
    _pizzaId = config.findPizzaIdByName(pizzaName);

    if (_pizzaId.empty()) {
        std::cerr << "Warning: Unknown pizza name: " << pizzaName << ", defaulting to margarita" << std::endl;
        _pizzaId = "margarita";
    }

    _initializeFromConfig();
}

/**
 * @brief Initialize pizza data from configuration
 */
void Pizza::_initializeFromConfig()
{
    auto& config = PizzaConfig::getInstance();

    if (!config.pizzaExists(_pizzaId)) {
        std::cerr << "Warning: Unknown pizza ID: " << _pizzaId << ", defaulting to margarita" << std::endl;
        _pizzaId = "margarita";
    }

    try {
        const auto& pizzaDef = config.getPizzaDefinition(_pizzaId);
        _pizzaName = pizzaDef.name;
        _ingredients = pizzaDef.ingredients;
        _baseCookingTime = pizzaDef.cookingTime;
    } catch (const std::exception& e) {
        std::cerr << "Error loading pizza configuration: " << e.what() << std::endl;
        _pizzaName = "Unknown";
        _baseCookingTime = 2;
    }
}

/**
 * @brief Destructor for the Pizza class
 */
Pizza::~Pizza()
{
}

/**
 * @brief Get the pizza ID
 */
std::string Pizza::getPizzaId() const
{
    return _pizzaId;
}

/**
 * @brief Get the pizza name
 */
std::string Pizza::getPizzaName() const
{
    return _pizzaName;
}

/**
 * @brief Get the size of pizza
 */
PizzaSize Pizza::getSize() const
{
    return _size;
}

/**
 * @brief Get the size as string
 */
std::string Pizza::getSizeString() const
{
    return PizzaConfig::sizeToString(_size);
}

/**
 * @brief Get the order ID this pizza belongs to
 */
int Pizza::getOrderId() const
{
    return _orderId;
}

/**
 * @brief Get the full name of the pizza (name + size)
 */
std::string Pizza::getName() const
{
    return _pizzaName + " " + getSizeString();
}

/**
 * @brief Get the base cooking time in seconds
 */
int Pizza::getCookingTime() const
{
    return _baseCookingTime;
}

/**
 * @brief Get the actual cooking time with multiplier applied
 */
float Pizza::getActualCookingTime(float multiplier) const
{
    if (multiplier <= 0.0f || multiplier > 100.0f) {
        std::cerr << "Warning: Invalid cooking time multiplier ("
                  << multiplier << "), using default of 1.0" << std::endl;
        multiplier = 1.0f;
    }

    float cookingTime = _baseCookingTime * multiplier;
    if (cookingTime <= 0.0f) {
        std::cerr << "Warning: Invalid cooking time calculated ("
                  << cookingTime << "), using default of "
                  << _baseCookingTime
                  << " seconds" << std::endl;
        return _baseCookingTime;
    }

    return cookingTime;
}

/**
 * @brief Get the ingredients for this pizza
 */
const std::vector<std::string>& Pizza::getIngredients() const
{
    return _ingredients;
}

/**
 * @brief Get legacy type number for backward compatibility
 */
int Pizza::getLegacyType() const
{
    std::hash<std::string> hasher;
    return static_cast<int>(hasher(_pizzaId) % 1000) + 1;
}

/**
 * @brief Serialize the pizza for IPC communication
 */
std::string Pizza::pack() const
{
    try {
        std::stringstream ss;
        ss << _pizzaId << ":" << getSizeString() << ":" << _orderId;
        return ss.str();
    } catch (const std::exception& e) {
        std::cerr << "Error packing pizza: " << e.what() << std::endl;
        return "Invalid";
    }
}

/**
 * @brief Deserialize a pizza from IPC data
 */
Pizza Pizza::unpack(const std::string& data)
{
    if (data.empty() || data == "Invalid")
        return Pizza("margarita", S);

    size_t firstDelimiterPos = data.find(':');
    if (firstDelimiterPos == std::string::npos)
        return Pizza("margarita", S);

    size_t secondDelimiterPos = data.find(':', firstDelimiterPos + 1);

    std::string pizzaId = data.substr(0, firstDelimiterPos);
    std::string sizeStr;
    int orderId = 0;

    if (secondDelimiterPos == std::string::npos) {
        sizeStr = data.substr(firstDelimiterPos + 1);
    } else {
        sizeStr = data.substr(firstDelimiterPos + 1,
            secondDelimiterPos - firstDelimiterPos - 1);
        try {
            orderId = std::stoi(data.substr(secondDelimiterPos + 1));
        } catch (...) {
            orderId = 0;
        }
    }

    PizzaSize size = PizzaConfig::stringToSize(sizeStr);
    return Pizza(pizzaId, size, orderId);
}

/**
 * @brief Set the order ID
 */
void Pizza::setOrderId(int orderId)
{
    _orderId = orderId;
}

/**
 * @brief Check if a pizza name is valid
 */
bool Pizza::isValidPizzaName(const std::string& name)
{
    auto& config = PizzaConfig::getInstance();
    return !config.findPizzaIdByName(name).empty();
}

/**
 * @brief Check if a size is valid
 */
bool Pizza::isValidSize(const std::string& size)
{
    auto sizes = PizzaConfig::getAllSizeNames();
    return std::find(sizes.begin(), sizes.end(), size) != sizes.end();
}

/**
 * @brief Get all available pizza names
 */
std::vector<std::string> Pizza::getAvailablePizzas()
{
    return PizzaConfig::getInstance().getAllPizzaNames();
}

/**
 * @brief Get all available sizes
 */
std::vector<std::string> Pizza::getAvailableSizes()
{
    return PizzaConfig::getAllSizeNames();
}

}
