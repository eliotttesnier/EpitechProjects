/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Input
*/

#pragma once

#include "AComponent.hpp"

class Input : public AComponent {
    public:
        //Constructor
        Input();
        ~Input() override = default;

        void simulate(std::size_t tick) override;

        //Setter
        void setState(nts::Tristate state);

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        //Getter
        std::pair<size_t, size_t> getPinInputs(std::size_t outputPin) const;

        nts::Tristate _state;
        nts::Tristate _previousState;
        bool _actualised;

        std::size_t _lastTick = 9999;
};
