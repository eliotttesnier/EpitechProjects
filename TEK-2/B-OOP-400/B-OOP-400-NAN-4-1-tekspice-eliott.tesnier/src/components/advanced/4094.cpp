/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4094
*/

#include "4094.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the 4094 component (Shift)
 */
C4094::C4094()
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
bool C4094::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= _nbPins && pin != 8 && pin != 16;
}

/**
 * @brief simulate the logic's component.
 *
 * @param tick The pin checked.
 */
void C4094::simulate(std::size_t tick)
{
    if (tick == _lastTick || _simulating)
        return;
    _lastTick = tick;
    _simulating = true;

    // Clock edge detection
    getLinkComponent(_clockPin).get()->simulate(tick);
    nts::Tristate clock = getLink(_clockPin);

    bool risingEdge = (_lastClockState == nts::Tristate::False && clock == nts::Tristate::True);
    _lastClockState = clock;

    // Data
    getLinkComponent(_dataPin).get()->simulate(tick);
    nts::Tristate data = getLink(_dataPin);

    if (clock == nts::Undefined || data == nts::Undefined || getLink(_outputEnablePin) == nts::Undefined || getLink(_strobePin) == nts::Undefined) {
        _lastQ1State = nts::Undefined;
        _lastQ2State = nts::Undefined;
        _lastQ3State = nts::Undefined;
        _lastQ4State = nts::Undefined;
        _lastQ5State = nts::Undefined;
        _lastQ6State = nts::Undefined;
        _lastQ7State = nts::Undefined;
        _lastQ8State = nts::Undefined;
        _lastQsState = nts::Undefined;
        _lastQeState = nts::Undefined;
        _simulating = false;
        return;
    }

    if (risingEdge) {
        _lastQ8State = _lastQ7State;
        _lastQ7State = _lastQ6State;
        _lastQ6State = _lastQ5State;
        _lastQ5State = _lastQ4State;
        _lastQ4State = _lastQ3State;
        _lastQ3State = _lastQ2State;
        _lastQ2State = _lastQ1State;
        _lastQ1State = data;
        _lastQsState = _lastQ7State;
    } else if (data == nts::True) {
        _lastQeState = _lastQ7State;
    }

    _simulating = false;
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4094::computeOutput(std::size_t pin)
{
    // Inputs
    if (pin == _clockPin || pin == _outputEnablePin || pin == _strobePin || pin == _dataPin)
        return getLink(pin);

    if (getLink(_clockPin) == nts::Undefined || getLink(_outputEnablePin) == nts::Undefined)
        return nts::Undefined;

    nts::Tristate output = nts::Tristate::Undefined;
    if (pin == _outpoutToPin[1])
        output = _lastQ1State;
    if (pin == _outpoutToPin[2])
        output = _lastQ2State;
    if (pin == _outpoutToPin[3])
        output = _lastQ3State;
    if (pin == _outpoutToPin[4])
        output = _lastQ4State;
    if (pin == _outpoutToPin[5])
        output = _lastQ5State;
    if (pin == _outpoutToPin[6])
        output = _lastQ6State;
    if (pin == _outpoutToPin[7])
        output = _lastQ7State;
    if (pin == _outpoutToPin[8])
        output = _lastQ8State;
    if (pin == _qsPin)
        output = _lastQsState;
    if (pin == _qePin)
        output = _lastQeState;
    return output;
}
