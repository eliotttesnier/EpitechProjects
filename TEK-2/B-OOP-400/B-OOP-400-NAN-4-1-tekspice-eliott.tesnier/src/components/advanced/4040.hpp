/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4040
*/

#pragma once

#include "AComponent.hpp"

class C4040 : public AComponent {
    public:
        C4040();
        ~C4040() override = default;

        void simulate(std::size_t tick) override;

    protected:
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        nts::Tristate _lastClockState = nts::Tristate::Undefined;
        std::size_t _lastTick = 9999;
        bool _simulating = false;
        unsigned int _counter;

        std::size_t _clockPin = 10;
        std::size_t _resetPin = 11;
        std::size_t _q1Pin = 9;
        std::size_t _q2Pin = 7;
        std::size_t _q3Pin = 6;
        std::size_t _q4Pin = 5;
        std::size_t _q5Pin = 3;
        std::size_t _q6Pin = 2;
        std::size_t _q7Pin = 4;
        std::size_t _q8Pin = 13;
        std::size_t _q9Pin = 12;
        std::size_t _q10Pin = 14;
        std::size_t _q11Pin = 15;
        std::size_t _q12Pin = 1;
};
