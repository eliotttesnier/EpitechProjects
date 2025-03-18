/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4040
*/

#include "4040.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the 4040 component (Counter)
 */
C4040::C4040()
{
    _nbPins = 16;
    _counter = 0;
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4040::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= _nbPins && pin != 8 && pin != 16; // 8 and 16 are power pins
}

/**
 * @brief simulate the logic's component.
 *
 * @param tick The pin checked.
 */
void C4040::simulate(std::size_t tick)
{
    if (tick == _lastTick || _simulating)
        return;
    _lastTick = tick;
    _simulating = true;

    // Assert clock and reset got simulated before
    getLinkComponent(_clockPin).get()->simulate(tick);
    getLinkComponent(_resetPin).get()->simulate(tick);
    nts::Tristate clock = getLink(_clockPin);
    nts::Tristate reset = getLink(_resetPin);

    if (reset == nts::Tristate::True) {
        _counter = 0;
        _lastClockState = clock;
        _simulating = false;
        return;
    }

    // Handle clock falling edge
    if (_lastClockState == nts::Tristate::True && clock == nts::Tristate::False) {
        _counter = (_counter + 1) & 0xFFF; // Keep only 12 bits
    }

    _lastClockState = clock;
    _simulating = false;
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4040::computeOutput(std::size_t pin)
{
    if (pin == _clockPin || pin == _resetPin)
        return getLink(pin);

    if (getLink(_resetPin) == nts::Tristate::True)
        return nts::Tristate::False;

    if (getLink(_clockPin) == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;

    // Match pin to counter bit
    int bit = 0;
    if (pin == _q1Pin) bit = 0;
    else if (pin == _q2Pin) bit = 1;
    else if (pin == _q3Pin) bit = 2;
    else if (pin == _q4Pin) bit = 3;
    else if (pin == _q5Pin) bit = 4;
    else if (pin == _q6Pin) bit = 5;
    else if (pin == _q7Pin) bit = 6;
    else if (pin == _q8Pin) bit = 7;
    else if (pin == _q9Pin) bit = 8;
    else if (pin == _q10Pin) bit = 9;
    else if (pin == _q11Pin) bit = 10;
    else if (pin == _q12Pin) bit = 11;

    // Return counter bit
    return (_counter & (1 << bit)) ? nts::Tristate::True : nts::Tristate::False;
}
