/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4094
*/

#pragma once

#include "AComponent.hpp"

class C4094 : public AComponent {
    public:
        C4094();
        ~C4094() override = default;

        void simulate(std::size_t tick) override;

    protected:
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;
        std::size_t _lastTick = 9999;
        bool _simulating = false;

        nts::Tristate _lastClockState = nts::Tristate::Undefined;
        nts::Tristate _lastQ1State = nts::Tristate::Undefined;
        nts::Tristate _lastQ2State = nts::Tristate::Undefined;
        nts::Tristate _lastQ3State = nts::Tristate::Undefined;
        nts::Tristate _lastQ4State = nts::Tristate::Undefined;
        nts::Tristate _lastQ5State = nts::Tristate::Undefined;
        nts::Tristate _lastQ6State = nts::Tristate::Undefined;
        nts::Tristate _lastQ7State = nts::Tristate::Undefined;
        nts::Tristate _lastQ8State = nts::Tristate::Undefined;
        nts::Tristate _lastQsState = nts::Tristate::Undefined;
        nts::Tristate _lastQeState = nts::Tristate::Undefined;

        std::map<size_t, size_t> _outpoutToPin = {
            {1, 4}, // Q1 -> 4
            {2, 5}, // Q2 -> 5
            {3, 6}, // Q3 -> 6
            {4, 7}, // Q4 -> 7
            {5, 14}, // Q5 -> 14
            {6, 13}, // Q6 -> 13
            {7, 12}, // Q7 -> 12
            {8, 11}, // Q8 -> 11
        };
        std::size_t _strobePin = 1;
        std::size_t _dataPin = 2;
        std::size_t _clockPin = 3;
        std::size_t _qsPin = 9;
        std::size_t _qePin = 10;
        std::size_t _outputEnablePin = 15;
};
