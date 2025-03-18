/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4013
*/

#pragma once

#include "AComponent.hpp"

class C4013 : public AComponent {
    public:
        C4013();
        ~C4013() override = default;

        void simulate(std::size_t tick) override;

    protected:
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        nts::Tristate computeFlipFlop(bool isFirstFlipFlop, nts::Tristate currentClock) const;

        // Store previous clock states and Q values
        nts::Tristate _lastClock1 = nts::False;
        nts::Tristate _lastClock2 = nts::False;
        nts::Tristate _q1 = nts::Undefined;
        nts::Tristate _q2 = nts::Undefined;

        std::size_t _clockPin1 = 3;
        std::size_t _clockPin2 = 11;
        std::size_t _resetPin1 = 4;
        std::size_t _resetPin2 = 10;
        std::size_t _dataPin1 = 5;
        std::size_t _dataPin2 = 9;
        std::size_t _setPin1 = 6;
        std::size_t _setPin2 = 8;
        std::size_t _qPin1 = 1;
        std::size_t _qPin2 = 13;
        std::size_t _qNotPin1 = 2;
        std::size_t _qNotPin2 = 12;

        std::size_t _lastTick = 9999;
        bool _simulating = false;
};
