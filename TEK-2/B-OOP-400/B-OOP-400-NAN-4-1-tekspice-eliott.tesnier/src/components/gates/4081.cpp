/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4081
*/

#include "4081.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component 4081 (AND gate with 2 inputs).
 */
C4081::C4081()
{
    _nbPins = 14;
    _andGates = {And(), And(), And(), And()};

    // First AND gate: inputs 1,2 -> output 3
    _andGates[0].setLink(1, *this, 1);
    _andGates[0].setLink(2, *this, 2);

    // Second AND gate: inputs 5,6 -> output 4
    _andGates[1].setLink(1, *this, 5);
    _andGates[1].setLink(2, *this, 6);

    // Third AND gate: inputs 8,9 -> output 10
    _andGates[2].setLink(1, *this, 8);
    _andGates[2].setLink(2, *this, 9);

    // Fourth AND gate: inputs 12,13 -> output 11
    _andGates[3].setLink(1, *this, 12);
    _andGates[3].setLink(2, *this, 13);
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4081::isValidPin(std::size_t pin) const
{
    return pin > 0 && pin <= _nbPins && pin != 7 && pin != 14;
}

/**
 * @brief Compute the AND (output) for the given pin.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4081::computeOutput(std::size_t pin)
{
    size_t andGateIndex;

    switch (pin) {
        case 3:
            andGateIndex = 0;
            break;
        case 4:
            andGateIndex = 1;
            break;
        case 10:
            andGateIndex = 2;
            break;
        case 11:
            andGateIndex = 3;
            break;
        default:
            return getLink(pin);
    }
    return _andGates[andGateIndex].compute(3);
}
