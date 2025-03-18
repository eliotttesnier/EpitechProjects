/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4514
*/

#include "4801.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the 4801 component (RAM)
 */
C4801::C4801()
{
    _nbPins = 24;
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4801::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= _nbPins && pin != 12 && pin != 24; // 8, 24 is power
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4801::computeOutput(std::size_t pin)
{
    (void)pin;
    return nts::Tristate::Undefined;
}
