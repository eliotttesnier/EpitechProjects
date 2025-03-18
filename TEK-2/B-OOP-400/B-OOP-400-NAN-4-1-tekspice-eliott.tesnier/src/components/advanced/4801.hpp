/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4801
*/

#pragma once

#include "AComponent.hpp"

class C4801 : public AComponent {
    public:
        C4801();
        ~C4801() override = default;

    protected:
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;
};
