/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4069
*/

#pragma once

#include "AComponent.hpp"
#include "Not.hpp"
#include <array>

class C4069 : public AComponent {
    public:
        //Constructor
        C4069();
        ~C4069() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        std::array<Not, 6> _notGates;
};
