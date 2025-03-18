/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** And
*/

#pragma once

#include "AComponent.hpp"

class And : public AComponent {
    public:
        //Constructor
        And();
        ~And() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        //Getter
        std::pair<size_t, size_t> getPinInputs(std::size_t outputPin) const;
        bool _computing = false;
};
