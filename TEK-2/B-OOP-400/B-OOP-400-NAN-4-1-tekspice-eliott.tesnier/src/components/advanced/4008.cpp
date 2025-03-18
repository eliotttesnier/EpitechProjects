/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4008
*/

#include "4008.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the 4008 component (Adder)
 */
C4008::C4008()
{
    _nbPins = 16;

    const std::array<std::pair<size_t, size_t>, 4> pinMapping = {{
        {7, 6},   // Bit 0 (A1, B1)
        {5, 4},   // Bit 1 (A2, B2)
        {3, 2},   // Bit 2 (A3, B3)
        {1, 15}   // Bit 3 (A4, B4)
    }};

    for (size_t i = 0; i < 4; i++) {
        auto [pinA, pinB] = pinMapping[i];

        _xorGates[i * 2].setLink(1, *this, pinA);
        _xorGates[i * 2].setLink(2, *this, pinB);

        _andGates[i * 2].setLink(1, *this, pinA);
        _andGates[i * 2].setLink(2, *this, pinB);

        _xorGates[i * 2 + 1].setLink(1, _xorGates[i * 2], 3);

        _andGates[i * 2 + 1].setLink(1, _xorGates[i * 2], 3);

        _orGates[i].setLink(1, _andGates[i * 2], 3);
        _orGates[i].setLink(2, _andGates[i * 2 + 1], 3);
    }
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4008::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= 16;
}

/**
 * @brief compute the Sum of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4008::computeSum(size_t bitIndex)
{
    // Set carry input
    if (bitIndex == 0) {
        _xorGates[bitIndex * 2 + 1].setLink(2, *this, 9);
        _andGates[bitIndex * 2 + 1].setLink(2, *this, 9);
    } else {
        _xorGates[bitIndex * 2 + 1].setLink(2, _orGates[bitIndex - 1], 3);
        _andGates[bitIndex * 2 + 1].setLink(2, _orGates[bitIndex - 1], 3);
    }

    // Force computation of previous carries
    for (size_t i = 0; i < bitIndex; ++i) {
        if (i == 0) {
            _andGates[i * 2 + 1].setLink(2, *this, 9);
        } else {
            _andGates[i * 2 + 1].setLink(2, _orGates[i - 1], 3);
        }
        _orGates[i].compute(3);
    }

    return _xorGates[bitIndex * 2 + 1].compute(3);
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4008::computeOutput(std::size_t pin)
{
    if (pin <= 9 || pin == 15)
        return getLink(pin);

    if (pin >= 10 && pin <= 13)
        return computeSum(pin - 10);

    if (pin == 14) {
        // Force computation of all carries from LSB to MSB
        for (size_t i = 0; i < 4; ++i) {
            if (i == 0) {
                _andGates[i * 2 + 1].setLink(2, *this, 9);
            } else {
                _andGates[i * 2 + 1].setLink(2, _orGates[i - 1], 3);
            }
            _orGates[i].compute(3);
        }
        return _orGates[3].compute(3);
    }

    return nts::Tristate::Undefined;
}
