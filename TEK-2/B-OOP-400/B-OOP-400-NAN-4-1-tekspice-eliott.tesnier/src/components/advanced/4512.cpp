/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4512
*/

#include "4512.hpp"

// Constructor

/**
 * @brief Constructor for the 4512 component (Selector)
 */
C4512::C4512()
{
    _nbPins = 16;
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4512::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= _nbPins;
}

/**
 * @brief compute the Multiplexer of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4512::computeMultiplexer() const
{
    nts::Tristate a = getLink(11);
    nts::Tristate b = getLink(12);
    nts::Tristate c = getLink(13);

    if (a == nts::Undefined || b == nts::Undefined || c == nts::Undefined)
        return nts::Undefined;

    int address = 0;
    address |= (a == nts::True ? 1 : 0);
    address |= (b == nts::True ? 2 : 0);
    address |= (c == nts::True ? 4 : 0);

    std::size_t inputPin;
    switch (address) {
        case 0: inputPin = 1; break;
        case 1: inputPin = 2; break;
        case 2: inputPin = 3; break;
        case 3: inputPin = 4; break;
        case 4: inputPin = 5; break;
        case 5: inputPin = 6; break;
        case 6: inputPin = 7; break;
        case 7: inputPin = 9; break;
    }
    return getLink(inputPin);
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4512::computeOutput(std::size_t pin)
{
    if (pin == 8 || pin == 16)
        return nts::Tristate::Undefined;

    if ((pin >= 1 && pin <= 7) || pin == 9 || pin == 10 || pin == 11 || pin == 12 || pin == 13 || pin == 15)
        return getLink(pin);

    // pin == 14
    nts::Tristate inhibit = getLink(10);
    nts::Tristate oe = getLink(15);
    if (oe == nts::True)
        return nts::Undefined;
    if (inhibit == nts::True)
        return nts::False;
    if (inhibit == nts::Undefined || oe == nts::Undefined)
        return nts::Undefined;
    return computeMultiplexer();
}
