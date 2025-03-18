/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4514
*/

#pragma once

#include "AComponent.hpp"

class C4514 : public AComponent {
    public:
        C4514();
        ~C4514() override = default;

        void simulate(std::size_t tick) override;
    protected:
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        nts::Tristate computeDecoder(size_t outputPin) const;

        std::map<int, int> _pinToOutput = {
            {4, 7},   // S7
            {5, 6},   // S6
            {6, 5},   // S5
            {7, 4},   // S4
            {8, 3},   // S3
            {9, 1},   // S1
            {10, 2},  // S2
            {11, 0},  // S0
            {13, 13}, // S13
            {14, 12}, // S12
            {15, 15}, // S15
            {16, 14}, // S14
            {17, 9},  // S9
            {18, 8},  // S8
            {19, 11}, // S11
            {20, 10}, // S10
        };
        std::map<size_t, nts::Tristate> _lastOutputs;
        std::size_t _lastTick = 9999;
        bool _simulating = false;
};
