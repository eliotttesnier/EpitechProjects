/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4512
*/

#pragma once

#include "AComponent.hpp"

class C4512 : public AComponent {
public:
    C4512();
    ~C4512() override = default;

protected:
    bool isValidPin(std::size_t pin) const override;
    nts::Tristate computeOutput(std::size_t pin) override;

private:
    nts::Tristate computeMultiplexer() const;
    std::map<size_t, nts::Tristate> _lastOutputs;
    std::size_t _lastTick = 9999;
    bool _simulating = false;
};