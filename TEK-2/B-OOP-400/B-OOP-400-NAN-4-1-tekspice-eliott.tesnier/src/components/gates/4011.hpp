/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4011
*/

#pragma once

#include "AComponent.hpp"
#include "And.hpp"
#include "Not.hpp"
#include <array>

class C4011 : public AComponent {
    public:
        //Constructor
        C4011();
        ~C4011() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        std::array<And, 4> _andGates;
        std::array<Not, 4> _notGates;
};
