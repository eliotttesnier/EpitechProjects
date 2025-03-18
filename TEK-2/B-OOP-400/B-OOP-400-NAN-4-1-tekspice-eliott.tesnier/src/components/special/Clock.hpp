/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Clock
*/

#pragma once

#include "AComponent.hpp"

class Clock : public AComponent {
    public:
        //Constructor
        Clock();
        ~Clock() override = default;

        void simulate(std::size_t tick) override;
        void setState(nts::Tristate state);

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        nts::Tristate _state;
        nts::Tristate _previousState;
        bool _actualised;
        std::size_t _lastTick = 9999;
};
