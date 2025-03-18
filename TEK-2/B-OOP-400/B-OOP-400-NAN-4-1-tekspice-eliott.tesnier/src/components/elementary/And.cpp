/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** And
*/

#include "And.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the AND component (AND gate).
 */
And::And()
{
    _nbPins = 3;
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool And::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= 3;
}

/**
 * @brief Compute the AND (output) for the given pin.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate And::computeOutput(std::size_t pin)
{
    if (_computing)
        return nts::Tristate::Undefined;

    if (pin != 3)
        return nts::Tristate::Undefined;

    _computing = true;
    auto [pin1, pin2] = getPinInputs(pin);
    nts::Tristate input1 = getLink(pin1);
    nts::Tristate input2 = getLink(pin2);
    _computing = false;

    if (input1 == nts::Tristate::False || input2 == nts::Tristate::False)
        return nts::Tristate::False;
    if (input1 == nts::Tristate::True && input2 == nts::Tristate::True)
        return nts::Tristate::True;
    return nts::Tristate::Undefined;
}

// Getter

/**
 * @brief Getter for the input pins of the AND gate output pin.
 *
 * @param outputPin The output pin checked.
 *
 * @return std::pair<size_t, size_t> The pair of input pins.
 */
std::pair<size_t, size_t> And::getPinInputs(std::size_t outputPin) const
{
    (void)outputPin;
    return {1, 2};
}
