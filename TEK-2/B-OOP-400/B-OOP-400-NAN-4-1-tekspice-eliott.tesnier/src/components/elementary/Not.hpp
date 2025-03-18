/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Not
*/

#pragma once

#include "AComponent.hpp"

class Not : public AComponent {
    public:
        //Constructor
        Not();
        ~Not() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        //Getter
        std::size_t getPinInputs(std::size_t outputPin) const;
        bool _computing = false;
};
