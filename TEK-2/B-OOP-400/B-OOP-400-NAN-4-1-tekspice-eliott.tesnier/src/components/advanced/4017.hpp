/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4017
*/

#pragma once

#include "AComponent.hpp"

class C4017 : public AComponent {
    public:
        C4017();
        ~C4017() override = default;

        void simulate(std::size_t tick) override;
    protected:
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        int _counter = 0;
        nts::Tristate _prevClockCp0;
        nts::Tristate _prevClockCp1;
        std::size_t _lastTick = 9999;
        bool _simulating = false;

        // Pin mapping
        static const std::size_t _q5Pin = 1;
        static const std::size_t _q1Pin = 2;
        static const std::size_t _q0Pin = 3;
        static const std::size_t _q2Pin = 4;
        static const std::size_t _q6Pin = 5;
        static const std::size_t _q7Pin = 6;
        static const std::size_t _q3Pin = 7;
        static const std::size_t _q8Pin = 9;
        static const std::size_t _q4Pin = 10;
        static const std::size_t _q9Pin = 11;
        static const std::size_t _q59Pin = 12;
        static const std::size_t _cp1Pin = 13;
        static const std::size_t _cp0Pin = 14;
        static const std::size_t _mrPin = 15;
};
