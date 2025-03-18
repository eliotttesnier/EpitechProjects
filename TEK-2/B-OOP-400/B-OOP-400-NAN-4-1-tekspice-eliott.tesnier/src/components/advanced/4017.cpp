/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4017
*/

#include "4017.hpp"
#include "Error.hpp"

C4017::C4017()
{
    _nbPins = 15;
    _prevClockCp0 = nts::False;
    _prevClockCp1 = nts::False;
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4017::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= 15 && pin != 8; // 8 is power
}

/**
 * @brief simulate the logic's component.
 *
 * @param tick The pin checked.
 */
void C4017::simulate(std::size_t tick)
{
    if (tick == _lastTick || _simulating)
        return;
    _lastTick = tick;
    _simulating = true;

    // (Ensure that the component is simulated)
    getLinkComponent(_cp0Pin)->simulate(tick);
    getLinkComponent(_cp1Pin)->simulate(tick);
    getLinkComponent(_mrPin)->simulate(tick);

    nts::Tristate cp0 = getLink(_cp0Pin);
    nts::Tristate cp1 = getLink(_cp1Pin);
    nts::Tristate mr = getLink(_mrPin);

    if (mr == nts::Undefined || cp0 == nts::Undefined || cp1 == nts::Undefined) {
        _counter = 0;
        _prevClockCp0 = nts::False;
        _prevClockCp1 = nts::False;
        _simulating = false;
        return;
    }

    if (mr == nts::True) {
        _counter = 0;
        _prevClockCp0 = nts::False;
        _prevClockCp1 = nts::False;
        _simulating = false;
        return;
    }

    if ((cp0 == nts::True && _prevClockCp0 == nts::False && cp1 == nts::True)
        || (cp1 == nts::True && _prevClockCp1 == nts::False && cp0 == nts::True)) {
        _counter = (_counter + 1) % 10;
    }
    _prevClockCp0 = cp0;
    _prevClockCp1 = cp1;
    _simulating = false;
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4017::computeOutput(std::size_t pin)
{
    nts::Tristate cp0 = getLink(_cp0Pin);
    nts::Tristate cp1 = getLink(_cp1Pin);
    nts::Tristate mr = getLink(_mrPin);

    if (pin == _cp0Pin || pin == _cp1Pin || pin == _mrPin)
        return getLink(pin);

    if (mr == nts::Undefined || cp0 == nts::Undefined || cp1 == nts::Undefined)
        return nts::Undefined;

    if (pin == _q0Pin) return (_counter == 0) ? nts::True : nts::False;
    if (pin == _q1Pin) return (_counter == 1) ? nts::True : nts::False;
    if (pin == _q2Pin) return (_counter == 2) ? nts::True : nts::False;
    if (pin == _q3Pin) return (_counter == 3) ? nts::True : nts::False;
    if (pin == _q4Pin) return (_counter == 4) ? nts::True : nts::False;
    if (pin == _q5Pin) return (_counter == 5) ? nts::True : nts::False;
    if (pin == _q6Pin) return (_counter == 6) ? nts::True : nts::False;
    if (pin == _q7Pin) return (_counter == 7) ? nts::True : nts::False;
    if (pin == _q8Pin) return (_counter == 8) ? nts::True : nts::False;
    if (pin == _q9Pin) return (_counter == 9) ? nts::True : nts::False;

    return (_counter >= 5 && _counter <= 9) ? nts::False : nts::True;
}
