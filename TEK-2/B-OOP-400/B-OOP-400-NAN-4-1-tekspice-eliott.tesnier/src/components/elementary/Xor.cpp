/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Xor
*/

#include "Xor.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the XOR component (XOR gate).
 * Initializes the XOR gate with 3 pins: 2 input pins and 1 output pin.
 */
Xor::Xor()
{
    _nbPins = 3;
}

// Method

/**
 * @brief Check if the given pin is valid for this component.
 *
 * @param pin The pin to check.
 *
 * @return bool True if the pin is valid, false otherwise.
 */
bool Xor::isValidPin(std::size_t pin) const
{
    return pin > 0 && pin <= _nbPins;
}

/**
 * @brief Compute the output of the XOR gate.
 * The XOR gate outputs True if exactly one input is True.
 *
 * @param pin The output pin to compute.
 *
 * @return nts::Tristate The computed output value.
 */
nts::Tristate Xor::computeOutput(std::size_t pin)
{
    if (_computing)
        return nts::Tristate::Undefined;

    _computing = true;
    auto [pin1, pin2] = getPinInputs(pin);
    nts::Tristate input1 = getLink(pin1);
    nts::Tristate input2 = getLink(pin2);
    _computing = false;

    if (input1 == nts::Tristate::Undefined || input2 == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;
    return (input1 != input2) ? nts::Tristate::True : nts::Tristate::False;
}

// Getter

/**
 * @brief Get the input pins associated with the given output pin.
 * The XOR gate takes two inputs and produces an output.
 *
 * @param outputPin The output pin to check.
 *
 * @return std::pair<size_t, size_t> The pair of input pins.
 *
 * @throws nts::InvalidArgument if the output pin is invalid.
 */
std::pair<size_t, size_t> Xor::getPinInputs(std::size_t outputPin) const
{
    (void)outputPin;
    return {1, 2};
}
