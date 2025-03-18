/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 2716
*/

#pragma once

#include "AComponent.hpp"

class C2716 : public AComponent {
    public:
        C2716();
        ~C2716() override = default;

        void simulate(std::size_t tick) override;

    protected:
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

        std::size_t _lastTick = 9999;
        bool _simulating = false;

        std::map<std::string, std::size_t> _InputToPin = {
            {"enable", 18},
            {"read", 20},
            {"addr_00", 8},
            {"addr_01", 7},
            {"addr_02", 6},
            {"addr_03", 5},
            {"addr_04", 4},
            {"addr_05", 3},
            {"addr_06", 2},
            {"addr_07", 1},
            {"addr_08", 23},
            {"addr_09", 22},
            {"addr_10", 19},
        };
        std::map<std::string, std::size_t> _OutputToPin = {
            {"out_0", 9},
            {"out_1", 10},
            {"out_2", 11},
            {"out_3", 13},
            {"out_4", 14},
            {"out_5", 15},
            {"out_6", 16},
            {"out_7", 17},
        };
};
