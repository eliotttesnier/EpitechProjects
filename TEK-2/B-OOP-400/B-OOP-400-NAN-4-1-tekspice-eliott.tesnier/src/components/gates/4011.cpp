/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4011
*/

#include "4011.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component 4011 (Quad 2-input NAND gate).
 */
C4011::C4011()
{
    _nbPins = 14;
    _andGates = {And(), And(), And(), And()};
    _notGates = {Not(), Not(), Not(), Not()};

    // First NAND gate: inputs 1,2 -> output 3
    _andGates[0].setLink(1, *this, 1);
    _andGates[0].setLink(2, *this, 2);
    _notGates[0].setLink(1, _andGates[0], 3);

    // Second NAND gate: inputs 5,6 -> output 4
    _andGates[1].setLink(1, *this, 5);
    _andGates[1].setLink(2, *this, 6);
    _notGates[1].setLink(1, _andGates[1], 3);

    // Third NAND gate: inputs 8,9 -> output 10
    _andGates[2].setLink(1, *this, 8);
    _andGates[2].setLink(2, *this, 9);
    _notGates[2].setLink(1, _andGates[2], 3);

    // Fourth NAND gate: inputs 12,13 -> output 11
    _andGates[3].setLink(1, *this, 12);
    _andGates[3].setLink(2, *this, 13);
    _notGates[3].setLink(1, _andGates[3], 3);
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4011::isValidPin(std::size_t pin) const
{
    return pin > 0 && pin <= _nbPins && pin != 7 && pin != 14;
}

/**
 * @brief Compute the NAND output for the given pin.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4011::computeOutput(std::size_t pin)
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
    return _notGates[gateIndex].compute(2);
}
