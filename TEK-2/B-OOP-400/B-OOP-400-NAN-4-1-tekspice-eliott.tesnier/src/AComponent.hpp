/*
** EPITECH PROJECT, 2024
** NTS
** File description:
** AComponent
*/

#pragma once

#include "IComponent.hpp"
#include <map>
#include <memory>
#include <iostream>

class AComponent : public nts::IComponent {
    public:
        // Constructor
        AComponent();
        ~AComponent() override;

        // Member functions
        void simulate(std::size_t tick) override;
        nts::Tristate compute(std::size_t pin) override;

        // Setters
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        // Getters
        nts::Tristate getLink(std::size_t pin) const;
        std::shared_ptr<nts::IComponent> getLinkComponent(std::size_t pin) const;

    protected:
        std::map<std::size_t, std::pair<std::shared_ptr<nts::IComponent>, std::size_t>> _links;
        std::size_t _nbPins;

        virtual bool isValidPin(std::size_t pin) const = 0;
        virtual nts::Tristate computeOutput(std::size_t pin) = 0;
};
