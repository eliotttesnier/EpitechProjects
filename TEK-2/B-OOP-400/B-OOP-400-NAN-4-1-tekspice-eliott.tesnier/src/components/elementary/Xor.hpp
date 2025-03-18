/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Xor
*/

#pragma once

#include "AComponent.hpp"

class Xor : public AComponent {
    public:
        //Constructor
        Xor();
        ~Xor() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        //Getter
        std::pair<size_t, size_t> getPinInputs(std::size_t outputPin) const;
        bool _computing = false;
};
