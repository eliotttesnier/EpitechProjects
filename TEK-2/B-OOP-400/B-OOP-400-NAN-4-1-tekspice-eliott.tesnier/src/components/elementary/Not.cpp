/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Not
*/

#include "Not.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the NOT component (NOT gate).
 * Initializes the NOT gate with 2 pins: 1 input pin and 1 output pin.
 */
Not::Not()
{
    _nbPins = 2;
}

// Method

/**
 * @brief Check if the given pin is valid for this component.
 *
 * @param pin The pin to check.
 *
 * @return bool True if the pin is valid, false otherwise.
 */
bool Not::isValidPin(std::size_t pin) const
{
    return pin > 0 && pin <= _nbPins;
}

/**
 * @brief Compute the output of the NOT gate.
 * The NOT gate outputs the inverse of its input.
 *
 * @param pin The output pin to compute.
 *
 * @return nts::Tristate The computed output value.
 */
nts::Tristate Not::computeOutput(std::size_t pin)
{
    if (_computing)
        return nts::Tristate::Undefined;

    if (pin != 2)
        return nts::Tristate::Undefined;

    _computing = true;
    auto inputPin = getPinInputs(pin);
    nts::Tristate input = getLink(inputPin);
    _computing = false;

    if (input == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;
    return input == nts::Tristate::True ? nts::Tristate::False : nts::Tristate::True;
}

// Getter

/**
 * @brief Get the input pin associated with the given output pin.
 * The NOT gate takes one input and produces an output.
 *
 * @param outputPin The output pin to check.
 *
 * @return std::pair<size_t, size_t> The input pin number (second value is unused).
 *
 * @throws nts::InvalidArgument if the output pin is invalid.
 */
std::size_t Not::getPinInputs(std::size_t outputPin) const
{
    (void)outputPin;
    return 1;
}
