/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4001
*/

#include "4001.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component 4001.
 */
C4001::C4001()
{
    _nbPins = 14;
    _orGates = {Or(), Or(), Or(), Or()};
    _notGates = {Not(), Not(), Not(), Not()};

    // First NOR gate: inputs 1,2 -> output 3
    _orGates[0].setLink(1, *this, 1);
    _orGates[0].setLink(2, *this, 2);
    _notGates[0].setLink(1, _orGates[0], 3);

    // Second NOR gate: inputs 5,6 -> output 4
    _orGates[1].setLink(1, *this, 5);
    _orGates[1].setLink(2, *this, 6);
    _notGates[1].setLink(1, _orGates[1], 3);

    // Third NOR gate: inputs 8,9 -> output 10
    _orGates[2].setLink(1, *this, 8);
    _orGates[2].setLink(2, *this, 9);
    _notGates[2].setLink(1, _orGates[2], 3);

    // Fourth NOR gate: inputs 12,13 -> output 11
    _orGates[3].setLink(1, *this, 12);
    _orGates[3].setLink(2, *this, 13);
    _notGates[3].setLink(1, _orGates[3], 3);
}

//Method

/**
 * @brief Check the pin of the component.
 *
 * @param pin the pin checked
 *
 * @return bool.
 */
bool C4001::isValidPin(std::size_t pin) const
{
    return pin > 0 && pin <= _nbPins && pin != 7 && pin != 14;
}

/**
 * @brief check the intput of the component.
 *
 * @param pin the pin checked
 *
 * @return nst::Tristate.
 */
nts::Tristate C4001::computeOutput(std::size_t pin)
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
