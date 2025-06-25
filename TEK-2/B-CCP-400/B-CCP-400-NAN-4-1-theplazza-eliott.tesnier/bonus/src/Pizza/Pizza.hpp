/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Pizza
*/

#pragma once

#include <string>
#include <vector>
#include "PizzaConfig.hpp"

namespace Pizza {

    class Pizza {
        public:
            Pizza(const std::string& pizzaId, PizzaSize size, int orderId = 0);

            Pizza(const std::string& pizzaName, const std::string& sizeStr, int orderId = 0);

            ~Pizza();

            std::string getPizzaId() const;
            std::string getPizzaName() const;
            PizzaSize getSize() const;
            std::string getSizeString() const;
            int getOrderId() const;
            std::string getName() const;
            int getCookingTime() const;
            float getActualCookingTime(float multiplier) const;
            const std::vector<std::string>& getIngredients() const;

            int getLegacyType() const;

            std::string pack() const;
            static Pizza unpack(const std::string& data);

            void setOrderId(int orderId);

            static bool isValidPizzaName(const std::string& name);
            static bool isValidSize(const std::string& size);
            static std::vector<std::string> getAvailablePizzas();
            static std::vector<std::string> getAvailableSizes();

        private:
            std::string _pizzaId;
            PizzaSize _size;
            int _orderId;
            std::vector<std::string> _ingredients;
            int _baseCookingTime;
            std::string _pizzaName;

            void _initializeFromConfig();
    };

};
