/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4030
*/

#include "4030.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component 4030 (Quad 2-input XOR gate).
 */
C4030::C4030()
{
    _nbPins = 14;
    _xorGates = {Xor(), Xor(), Xor(), Xor()};

    // First XOR gate: inputs 1,2 -> output 3
    _xorGates[0].setLink(1, *this, 1);
    _xorGates[0].setLink(2, *this, 2);

    // Second XOR gate: inputs 5,6 -> output 4
    _xorGates[1].setLink(1, *this, 5);
    _xorGates[1].setLink(2, *this, 6);

    // Third XOR gate: inputs 8,9 -> output 10
    _xorGates[2].setLink(1, *this, 8);
    _xorGates[2].setLink(2, *this, 9);

    // Fourth XOR gate: inputs 12,13 -> output 11
    _xorGates[3].setLink(1, *this, 12);
    _xorGates[3].setLink(2, *this, 13);
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4030::isValidPin(std::size_t pin) const
{
    return pin > 0 && pin <= _nbPins && pin != 7 && pin != 14;
}

/**
 * @brief Compute the XOR output for the given pin.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4030::computeOutput(std::size_t pin)
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
    return _xorGates[gateIndex].compute(3);
}
