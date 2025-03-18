/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4071
*/

#include "4071.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component 4071 (OR gate with 2 inputs).
 */
C4071::C4071()
{
    _nbPins = 14;
    _orGates = {Or(), Or(), Or(), Or()};

    // First OR gate: inputs 1,2 -> output 3
    _orGates[0].setLink(1, *this, 1);
    _orGates[0].setLink(2, *this, 2);

    // Second OR gate: inputs 5,6 -> output 4
    _orGates[1].setLink(1, *this, 5);
    _orGates[1].setLink(2, *this, 6);

    // Third OR gate: inputs 8,9 -> output 10
    _orGates[2].setLink(1, *this, 8);
    _orGates[2].setLink(2, *this, 9);

    // Fourth OR gate: inputs 12,13 -> output 11
    _orGates[3].setLink(1, *this, 12);
    _orGates[3].setLink(2, *this, 13);
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4071::isValidPin(std::size_t pin) const
{
    return pin > 0 && pin <= _nbPins && pin != 7 && pin != 14;
}

/**
 * @brief Compute the OR (output) for the given pin.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4071::computeOutput(std::size_t pin)
{
    size_t gateIndex;

    switch (pin) {
        case 3:
            gateIndex = 0;
            break;
        case 4:
            gateIndex = 1;
            break;
        case 10:
            gateIndex = 2;
            break;
        case 11:
            gateIndex = 3;
            break;
        default:
            return getLink(pin);
    }
    return _orGates[gateIndex].compute(3);
}
