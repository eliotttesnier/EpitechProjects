/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Pizza
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Pizza {

    namespace Ingredients {
        const std::string DOUGH = "dough";
        const std::string TOMATO = "tomato";
        const std::string GRUYERE = "gruyere";
        const std::string HAM = "ham";
        const std::string MUSHROOMS = "mushrooms";
        const std::string STEAK = "steak";
        const std::string EGGPLANT = "eggplant";
        const std::string GOAT_CHEESE = "goat cheese";
        const std::string CHIEF_LOVE = "chief love";
    };

    enum PizzaType {Regina = 1, Margarita = 2, Americana = 4, Fantasia = 8};
    enum PizzaSize {S = 1, M = 2, L = 4, XL = 8, XXL = 16};

    const std::unordered_map<PizzaType, std::string> TYPE_NAMES = {
        {Regina, "Regina"}, {Margarita, "Margarita"},
        {Americana, "Americana"}, {Fantasia, "Fantasia"}
    };

    const std::unordered_map<PizzaSize, std::string> SIZE_NAMES = {
        {S, "S"}, {M, "M"}, {L, "L"},
        {XL, "XL"}, {XXL, "XXL"}
    };

    const std::unordered_map<PizzaType, int> COOKING_TIMES = {
        {Regina, 2}, {Margarita, 1},
        {Americana, 2}, {Fantasia, 4}
    };

    const std::unordered_map<PizzaType, std::vector<std::string>> PIZZA_INGREDIENTS = {
        {Regina, {Ingredients::DOUGH, Ingredients::TOMATO, Ingredients::GRUYERE, Ingredients::HAM, Ingredients::MUSHROOMS}},
        {Margarita, {Ingredients::DOUGH, Ingredients::TOMATO, Ingredients::GRUYERE}},
        {Americana, {Ingredients::DOUGH, Ingredients::TOMATO, Ingredients::GRUYERE, Ingredients::STEAK}},
        {Fantasia, {Ingredients::DOUGH, Ingredients::TOMATO, Ingredients::EGGPLANT, Ingredients::GOAT_CHEESE, Ingredients::CHIEF_LOVE}}
    };

    class Pizza {
        public:
            Pizza(PizzaType type, PizzaSize size, int orderId = 0);
            ~Pizza();

            PizzaType getType() const;
            PizzaSize getSize() const;
            int getOrderId() const;
            std::string getName() const;
            int getCookingTime() const;
            float getActualCookingTime(float multiplier) const;
            const std::vector<std::string>& getIngredients() const;

            std::string pack() const;
            static Pizza unpack(const std::string& data);

            void setOrderId(int orderId);

        private:
            PizzaType _type;
            PizzaSize _size;
            int _orderId;
            std::vector<std::string> _ingredients;
            int _baseCookingTime;
    };

};
