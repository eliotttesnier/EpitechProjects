/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4008
*/

#pragma once

#include "AComponent.hpp"
#include "And.hpp"
#include "Or.hpp"
#include "Xor.hpp"
#include <array>

class C4008 : public AComponent {
    public:
        C4008();
        ~C4008() override = default;

    protected:
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        std::array<Xor, 8> _xorGates;
        std::array<And, 8> _andGates;
        std::array<Or, 4> _orGates;

        nts::Tristate computeSum(size_t bitIndex);
};
