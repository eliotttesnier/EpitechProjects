/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Output
*/

#pragma once

#include "AComponent.hpp"

class Output : public AComponent {
    public:
        //Constructor
        Output();
        ~Output() override = default;

    protected:
        //Method
        bool isValidPin(std::size_t pin) const override;
        nts::Tristate computeOutput(std::size_t pin) override;

    private:
        //Getter
        std::pair<size_t, size_t> getPinInputs(std::size_t outputPin) const;
};
