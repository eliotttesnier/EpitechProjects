/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Pizza
*/

#include "Pizza.hpp"
#include <stdexcept>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

namespace Pizza {

/**
 * @brief Constructor for the Pizza class
 *
 * @param type The type of pizza
 * @param size The size of pizza
 * @param orderId The ID of the order this pizza belongs to
 */
Pizza::Pizza(PizzaType type, PizzaSize size, int orderId)
    : _type(type), _size(size), _orderId(orderId), _baseCookingTime(0)
{
    if (PIZZA_INGREDIENTS.count(type)) {
        _ingredients = PIZZA_INGREDIENTS.at(type);
    } else {
        std::cerr << "Warning: Unknown pizza type: " << static_cast<int>(type) << std::endl;
    }

    if (COOKING_TIMES.count(type)) {
        _baseCookingTime = COOKING_TIMES.at(type);
    } else {
        std::cerr << "Warning: No cooking time defined for pizza type: "
                  << static_cast<int>(type) << std::endl;
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
 * @brief Get the type of pizza
 *
 * @return The pizza type
 */
PizzaType Pizza::getType() const
{
    return _type;
}

/**
 * @brief Get the size of pizza
 *
 * @return The pizza size
 */
PizzaSize Pizza::getSize() const
{
    return _size;
}

/**
 * @brief Get the order ID this pizza belongs to
 *
 * @return The order ID
 */
int Pizza::getOrderId() const
{
    return _orderId;
}

/**
 * @brief Get the name of the pizza
 *
 * @return The pizza name (type and size)
 */
std::string Pizza::getName() const
{
    return TYPE_NAMES.at(_type) + " " + SIZE_NAMES.at(_size);
}

/**
 * @brief Get the base cooking time in seconds
 *
 * @return The base cooking time
 */
int Pizza::getCookingTime() const
{
    return _baseCookingTime;
}

/**
 * @brief Get the actual cooking time with multiplier applied
 *
 * @param multiplier The cooking time multiplier
 *
 * @return The actual cooking time in seconds
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
 *
 * @return Vector of ingredient names
 */
const std::vector<std::string>& Pizza::getIngredients() const
{
    return _ingredients;
}

/**
 * @brief Serialize the pizza for IPC communication
 *
 * @return Serialized string representation of the pizza
 */
std::string Pizza::pack() const
{
    try {
        std::stringstream ss;
        ss << TYPE_NAMES.at(_type) << ":" << SIZE_NAMES.at(_size) << ":" << _orderId;
        return ss.str();
    } catch (const std::out_of_range& e) {
        return "Invalid";
    }
}

/**
 * @brief Deserialize a pizza from IPC data
 *
 * @param data The serialized pizza data
 *
 * @return Constructed Pizza object
 */
Pizza Pizza::unpack(const std::string& data)
{
    if (data.empty() || data == "Invalid")
        return Pizza(Margarita, S);

    size_t firstDelimiterPos = data.find(':');
    if (firstDelimiterPos == std::string::npos)
        return Pizza(Margarita, S);

    size_t secondDelimiterPos = data.find(':', firstDelimiterPos + 1);

    std::string typeStr = data.substr(0, firstDelimiterPos);
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

    PizzaType type = Margarita;
    for (const auto& pair : TYPE_NAMES) {
        if (pair.second == typeStr) {
            type = pair.first;
            break;
        }
    }

    PizzaSize size = S;
    for (const auto& pair : SIZE_NAMES) {
        if (pair.second == sizeStr) {
            size = pair.first;
            break;
        }
    }

    return Pizza(type, size, orderId);
}

void Pizza::setOrderId(int orderId)
{
    _orderId = orderId;
}

}
