/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** PizzaConfig
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Pizza {

    struct PizzaDefinition {
        std::string name;
        std::string id;
        std::vector<std::string> ingredients;
        int cookingTime;
    };

    struct IngredientDefinition {
        std::string name;
        std::string id;
    };

    enum PizzaSize {S = 1, M = 2, L = 4, XL = 8, XXL = 16};

    class PizzaConfig {
        public:
            static PizzaConfig& getInstance();

            void loadPizzasFromJson(const std::string& filePath);
            void loadIngredientsFromJson(const std::string& filePath);

            bool pizzaExists(const std::string& pizzaId) const;
            const PizzaDefinition& getPizzaDefinition(const std::string& pizzaId) const;
            std::vector<std::string> getAllPizzaIds() const;
            std::vector<std::string> getAllPizzaNames() const;

            bool ingredientExists(const std::string& ingredientId) const;
            const IngredientDefinition& getIngredientDefinition(const std::string& ingredientId) const;
            std::vector<std::string> getAllIngredientIds() const;

            static std::string sizeToString(PizzaSize size);
            static PizzaSize stringToSize(const std::string& sizeStr);
            static std::vector<std::string> getAllSizeNames();

            std::string findPizzaIdByName(const std::string& name) const;
            void printAvailablePizzas() const;
            void printAvailableIngredients() const;

        private:
            PizzaConfig() = default;
            ~PizzaConfig() = default;
            PizzaConfig(const PizzaConfig&) = delete;
            PizzaConfig& operator=(const PizzaConfig&) = delete;

            std::unordered_map<std::string, PizzaDefinition> _pizzas;
            std::unordered_map<std::string, IngredientDefinition> _ingredients;

            static const std::unordered_map<PizzaSize, std::string> SIZE_NAMES;
            static const std::unordered_map<std::string, PizzaSize> NAME_TO_SIZE;
    };
}