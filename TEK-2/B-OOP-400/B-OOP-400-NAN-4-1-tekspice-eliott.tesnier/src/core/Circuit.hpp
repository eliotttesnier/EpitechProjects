/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** Circuit
*/

#pragma once

#include <map>
#include <memory>
#include <string>
#include "IComponent.hpp"
#include "Factory.hpp"

class Circuit {
    public:
        // Constructor
        Circuit();
        ~Circuit();

        void simulate();
        void display() const;

        // Component handling
        void addComponent(const std::string &name, const std::string &type, Factory &factory);
        bool hasComponent(const std::string &name) const;
        void linkComponents(const std::string &name1, std::size_t pin1, const std::string &name2, std::size_t pin2);


        // Input/Output handling
        void setInput(const std::string &name, nts::Tristate value);

        std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
    private:
        std::size_t _tick;

        void displayInputs() const;
        void displayOutputs() const;
};
