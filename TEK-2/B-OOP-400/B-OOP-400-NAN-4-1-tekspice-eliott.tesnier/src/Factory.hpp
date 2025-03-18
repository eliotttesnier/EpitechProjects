/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** Factory
*/

#pragma once

#include "IComponent.hpp"
#include <memory>
#include <map>
#include <functional>

class Factory {

    public:
        // Constructor
        Factory();
        ~Factory();

        // Member functions
        std::unique_ptr<nts::IComponent> createComponent(const std::string &type);

    private:
        std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> _creators;
};
