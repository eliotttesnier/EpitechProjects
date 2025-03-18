/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4001
*/

#pragma once

#include "AComponent.hpp"
#include "Or.hpp"
#include "Not.hpp"
#include <array>

class C4001 : public AComponent {
    public:
        //Constructor
        C4001();
        ~C4001() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        std::array<Or, 4> _orGates;
        std::array<Not, 4> _notGates;
};
