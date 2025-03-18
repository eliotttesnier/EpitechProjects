/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4013
*/

#include "4013.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the 4013 component (Flipflop)
 */
C4013::C4013()
{
    _nbPins = 14;
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4013::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= 14 && pin != 7 && pin != 14; // Pins 7,14 are power
}

/**
 * @brief compute the Flip flop of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4013::computeFlipFlop(bool isFirstFlipFlop, nts::Tristate currentClock) const
{
    nts::Tristate data = getLink(isFirstFlipFlop ? _dataPin1 : _dataPin2);
    nts::Tristate set = getLink(isFirstFlipFlop ? _setPin1 : _setPin2);
    nts::Tristate reset = getLink(isFirstFlipFlop ? _resetPin1 : _resetPin2);
    nts::Tristate lastClock = isFirstFlipFlop ? _lastClock1 : _lastClock2;
    nts::Tristate currentQ = isFirstFlipFlop ? _q1 : _q2;

    if (set == nts::True)
        return nts::True;
    if (reset == nts::True)
        return nts::False;

    if (currentClock == nts::Undefined || data == nts::Undefined || set == nts::Undefined || reset == nts::Undefined || lastClock == nts::Undefined)
        return nts::Undefined;

    bool risingEdge = (lastClock == nts::False && currentClock == nts::True);

    if (risingEdge)
        return data;
    return currentQ;
}

/**
 * @brief simulate the logic's component.
 *
 * @param tick The pin checked.
 */
void C4013::simulate(std::size_t tick)
{
    if (tick == _lastTick || _simulating)
        return;
    _lastTick = tick;
    _simulating = true;

    // Simulate every components linked to this one
    getLinkComponent(_clockPin1)->simulate(tick);
    getLinkComponent(_clockPin2)->simulate(tick);
    getLinkComponent(_resetPin1)->simulate(tick);
    getLinkComponent(_resetPin2)->simulate(tick);
    getLinkComponent(_dataPin1)->simulate(tick);
    getLinkComponent(_dataPin2)->simulate(tick);
    getLinkComponent(_setPin1)->simulate(tick);
    getLinkComponent(_setPin2)->simulate(tick);

    // Get current clock states
    nts::Tristate clock1 = getLink(_clockPin1);
    nts::Tristate clock2 = getLink(_clockPin2);

    // Compute new Q values
    _q1 = computeFlipFlop(true, clock1);
    _q2 = computeFlipFlop(false, clock2);

    // Update clock states for next tick
    _lastClock1 = clock1;
    _lastClock2 = clock2;
    _simulating = false;
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4013::computeOutput(std::size_t pin)
{
    // Only return values, no state updates here
    if (pin == _clockPin1 || pin == _clockPin2 ||
        pin == _resetPin1 || pin == _resetPin2 ||
        pin == _dataPin1 || pin == _dataPin2 ||
        pin == _setPin1 || pin == _setPin2)
        return getLink(pin);

    // Return cached Q values computed during simulate
    if (pin == _qPin1)
        return _q1;
    if (pin == _qPin2)
        return _q2;

    if (pin == _qNotPin1) {
        if (_q1 == nts::Undefined)
            return nts::Undefined;

        if (getLink(_resetPin1) == nts::Tristate::True &&
            getLink(_setPin1) == nts::Tristate::True)
            return nts::True;
        return  _q1 == nts::True ? nts::False : nts::True;
    }
    // pin == _qNotPin2
    if (_q2 == nts::Undefined)
        return nts::Undefined;

    if (getLink(_resetPin2) == nts::Tristate::True &&
        getLink(_setPin2) == nts::Tristate::True)
        return nts::True;
    return _q2 == nts::True ? nts::False : nts::True;
}
