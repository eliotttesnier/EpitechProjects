/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** PizzaConfig
*/

#include "PizzaConfig.hpp"
#include "../../lib/json.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

namespace Pizza {

const std::unordered_map<PizzaSize, std::string> PizzaConfig::SIZE_NAMES = {
    {S, "S"}, {M, "M"}, {L, "L"}, {XL, "XL"}, {XXL, "XXL"}
};

const std::unordered_map<std::string, PizzaSize> PizzaConfig::NAME_TO_SIZE = {
    {"S", S}, {"M", M}, {"L", L}, {"XL", XL}, {"XXL", XXL}
};

/**
 * @brief Get the singleton instance of PizzaConfig
 */
PizzaConfig& PizzaConfig::getInstance() {
    static PizzaConfig instance;
    return instance;
}

/**
 * @brief Load pizza definitions from JSON file
 */
void PizzaConfig::loadPizzasFromJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open pizzas config file: " + filePath);
    }

    nlohmann::json jsonData;
    try {
        file >> jsonData;
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error("Error parsing pizzas JSON: " + std::string(e.what()));
    }

    if (!jsonData.contains("pizzas") || !jsonData["pizzas"].is_array()) {
        throw std::runtime_error("Invalid pizzas JSON format: missing 'pizzas' array");
    }

    _pizzas.clear();
    for (const auto& pizzaJson : jsonData["pizzas"]) {
        if (!pizzaJson.contains("name") || !pizzaJson.contains("id") ||
            !pizzaJson.contains("ingredients") || !pizzaJson.contains("cookingTime")) {
            std::cerr << "Warning: Skipping invalid pizza entry" << std::endl;
            continue;
        }

        PizzaDefinition pizza;
        pizza.name = pizzaJson["name"];
        pizza.id = pizzaJson["id"];
        pizza.cookingTime = pizzaJson["cookingTime"];

        if (pizzaJson["ingredients"].is_array()) {
            for (const auto& ingredient : pizzaJson["ingredients"]) {
                pizza.ingredients.push_back(ingredient);
            }
        }

        _pizzas[pizza.id] = pizza;
    }

    std::cout << "Loaded " << _pizzas.size() << " pizza types from " << filePath << std::endl;
}

/**
 * @brief Load ingredient definitions from JSON file
 */
void PizzaConfig::loadIngredientsFromJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open ingredients config file: " + filePath);
    }

    nlohmann::json jsonData;
    try {
        file >> jsonData;
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error("Error parsing ingredients JSON: " + std::string(e.what()));
    }

    if (!jsonData.contains("ingredients") || !jsonData["ingredients"].is_array()) {
        throw std::runtime_error("Invalid ingredients JSON format: missing 'ingredients' array");
    }

    _ingredients.clear();
    for (const auto& ingredientJson : jsonData["ingredients"]) {
        if (!ingredientJson.contains("name") || !ingredientJson.contains("id")) {
            std::cerr << "Warning: Skipping invalid ingredient entry" << std::endl;
            continue;
        }

        IngredientDefinition ingredient;
        ingredient.name = ingredientJson["name"];
        ingredient.id = ingredientJson["id"];

        _ingredients[ingredient.id] = ingredient;
    }

    std::cout << "Loaded " << _ingredients.size() << " ingredients from " << filePath << std::endl;
}

/**
 * @brief Check if a pizza type exists
 */
bool PizzaConfig::pizzaExists(const std::string& pizzaId) const {
    return _pizzas.find(pizzaId) != _pizzas.end();
}

/**
 * @brief Get pizza definition by ID
 */
const PizzaDefinition& PizzaConfig::getPizzaDefinition(const std::string& pizzaId) const {
    auto it = _pizzas.find(pizzaId);
    if (it == _pizzas.end()) {
        throw std::runtime_error("Pizza not found: " + pizzaId);
    }
    return it->second;
}

/**
 * @brief Get all available pizza IDs
 */
std::vector<std::string> PizzaConfig::getAllPizzaIds() const {
    std::vector<std::string> ids;
    for (const auto& pair : _pizzas) {
        ids.push_back(pair.first);
    }
    return ids;
}

/**
 * @brief Get all available pizza names
 */
std::vector<std::string> PizzaConfig::getAllPizzaNames() const {
    std::vector<std::string> names;
    for (const auto& pair : _pizzas) {
        names.push_back(pair.second.name);
    }
    return names;
}

/**
 * @brief Check if an ingredient exists
 */
bool PizzaConfig::ingredientExists(const std::string& ingredientId) const {
    return _ingredients.find(ingredientId) != _ingredients.end();
}

/**
 * @brief Get ingredient definition by ID
 */
const IngredientDefinition& PizzaConfig::getIngredientDefinition(const std::string& ingredientId) const {
    auto it = _ingredients.find(ingredientId);
    if (it == _ingredients.end()) {
        throw std::runtime_error("Ingredient not found: " + ingredientId);
    }
    return it->second;
}

/**
 * @brief Get all available ingredient IDs
 */
std::vector<std::string> PizzaConfig::getAllIngredientIds() const {
    std::vector<std::string> ids;
    for (const auto& pair : _ingredients) {
        ids.push_back(pair.first);
    }
    return ids;
}

/**
 * @brief Convert pizza size enum to string
 */
std::string PizzaConfig::sizeToString(PizzaSize size) {
    auto it = SIZE_NAMES.find(size);
    if (it != SIZE_NAMES.end()) {
        return it->second;
    }
    return "Unknown";
}

/**
 * @brief Convert string to pizza size enum
 */
PizzaSize PizzaConfig::stringToSize(const std::string& sizeStr) {
    auto it = NAME_TO_SIZE.find(sizeStr);
    if (it != NAME_TO_SIZE.end()) {
        return it->second;
    }
    return S;
}

/**
 * @brief Get all size names
 */
std::vector<std::string> PizzaConfig::getAllSizeNames() {
    return {"S", "M", "L", "XL", "XXL"};
}

/**
 * @brief Find pizza ID by name (case-insensitive)
 */
std::string PizzaConfig::findPizzaIdByName(const std::string& name) const {
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& pair : _pizzas) {
        std::string lowerPizzaName = pair.second.name;
        std::transform(lowerPizzaName.begin(), lowerPizzaName.end(), lowerPizzaName.begin(), ::tolower);

        if (lowerPizzaName == lowerName) {
            return pair.second.id;
        }
    }
    return "";
}

/**
 * @brief Print all available pizzas
 */
void PizzaConfig::printAvailablePizzas() const {
    std::cout << "Available pizzas:" << std::endl;
    for (const auto& pair : _pizzas) {
        const auto& pizza = pair.second;
        std::cout << "  - " << pizza.name << " (id: " << pizza.id << ")" << std::endl;
        std::cout << "    Cooking time: " << pizza.cookingTime << "s" << std::endl;
        std::cout << "    Ingredients: ";
        for (size_t i = 0; i < pizza.ingredients.size(); ++i) {
            std::cout << pizza.ingredients[i];
            if (i < pizza.ingredients.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl << std::endl;
    }
}

/**
 * @brief Print all available ingredients
 */
void PizzaConfig::printAvailableIngredients() const {
    std::cout << "Available ingredients:" << std::endl;
    for (const auto& pair : _ingredients) {
        const auto& ingredient = pair.second;
        std::cout << "  - " << ingredient.name << " (id: " << ingredient.id << ")" << std::endl;
    }
}

}