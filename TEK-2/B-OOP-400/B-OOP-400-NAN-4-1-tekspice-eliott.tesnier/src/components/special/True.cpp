/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** True
*/

#include "True.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component True.
 */
True::True()
{
    _nbPins = 1;
}

//Method

/**
 * @brief Check the pin of the component.
 *
 * @param pin the pin checked
 *
 * @return bool.
 */
bool True::isValidPin(std::size_t pin) const
{
    return pin == 1;
}

/**
 * @brief check the output of the component.
 *
 * @param pin the pin checked
 *
 * @return nst::Tristate.
 */
nts::Tristate True::computeOutput(std::size_t pin)
{
    (void)pin;
    return nts::Tristate::True;
}
