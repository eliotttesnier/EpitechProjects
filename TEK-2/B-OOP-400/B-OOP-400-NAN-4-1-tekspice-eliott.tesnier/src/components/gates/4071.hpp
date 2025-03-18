/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4071
*/

#pragma once

#include "AComponent.hpp"
#include "Or.hpp"
#include <array>

class C4071 : public AComponent {
    public:
        //Constructor
        C4071();
        ~C4071() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        std::array<Or, 4> _orGates;
};
