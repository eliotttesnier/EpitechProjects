/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4071
*/

#include "4069.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component 4069 (Hex Inverter).
 */
C4069::C4069()
{
    _nbPins = 14;
    _notGates = {Not(), Not(), Not(), Not(), Not(), Not()};

    // First NOT gate: input 1 -> output 2
    _notGates[0].setLink(1, *this, 1);

    // Second NOT gate: input 3 -> output 4
    _notGates[1].setLink(1, *this, 3);

    // Third NOT gate: input 5 -> output 6
    _notGates[2].setLink(1, *this, 5);

    // Fourth NOT gate: input 9 -> output 8
    _notGates[3].setLink(1, *this, 9);

    // Fifth NOT gate: input 11 -> output 10
    _notGates[4].setLink(1, *this, 11);

    // Sixth NOT gate: input 13 -> output 12
    _notGates[5].setLink(1, *this, 13);
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4069::isValidPin(std::size_t pin) const
{
    return pin > 0 && pin <= _nbPins && pin != 7 && pin != 14;
}

/**
 * @brief Compute the NOT (inverter) output for the given pin.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4069::computeOutput(std::size_t pin)
{
    size_t gateIndex;

    switch (pin) {
        case 2:
            gateIndex = 0;
            break;
        case 4:
            gateIndex = 1;
            break;
        case 6:
            gateIndex = 2;
            break;
        case 8:
            gateIndex = 3;
            break;
        case 10:
            gateIndex = 4;
            break;
        case 12:
            gateIndex = 5;
            break;
        default:
            return getLink(pin);
    }
    return _notGates[gateIndex].compute(2);
}
