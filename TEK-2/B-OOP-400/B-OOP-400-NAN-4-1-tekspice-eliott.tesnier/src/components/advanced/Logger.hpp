/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** Logger
*/

#pragma once

#include "AComponent.hpp"
#include <vector>
#include <iostream>

class Logger : public AComponent {
    public:
        // Constructor
        Logger();
        ~Logger() override = default;

        // Method
        void simulate(std::size_t tick) override;
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        nts::Tristate _lastClock = nts::False;
        std::vector<nts::Tristate> _inputs;
        std::size_t _lastTick = 9999;
        bool _simulating = false;
        std::size_t _clockPin = 9;
        std::size_t _inhibitPin = 10;
        bool _risingEdge = false;
};
