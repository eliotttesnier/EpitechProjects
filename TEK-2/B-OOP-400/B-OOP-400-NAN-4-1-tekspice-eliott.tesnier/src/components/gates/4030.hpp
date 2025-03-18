/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4030
*/

#pragma once

#include "AComponent.hpp"
#include "Xor.hpp"
#include <array>

class C4030 : public AComponent {
    public:
        //Constructor
        C4030();
        ~C4030() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        std::array<Xor, 4> _xorGates;
};
