/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4081
*/

#pragma once

#include "AComponent.hpp"
#include "And.hpp"
#include <array>

class C4081 : public AComponent {
    public:
        //Constructor
        C4081();
        ~C4081() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        //Getter
        std::array<And, 4> _andGates;
};
