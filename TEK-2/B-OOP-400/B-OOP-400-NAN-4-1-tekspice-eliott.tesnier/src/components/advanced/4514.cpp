/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 4514
*/

#include "4514.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the 4514 component (Decoder)
 */
C4514::C4514()
{
    _nbPins = 24;
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool C4514::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= _nbPins;
}

/**
 * @brief simulate the logic's component.
 *
 * @param tick The pin checked.
 */
void C4514::simulate(std::size_t tick)
{
    if (tick == _lastTick || _simulating)
        return;
    _lastTick = tick;
    _simulating = true;

    getLinkComponent(1).get()->simulate(tick);
    getLinkComponent(23).get()->simulate(tick);
    getLinkComponent(2).get()->simulate(tick);
    getLinkComponent(3).get()->simulate(tick);
    getLinkComponent(21).get()->simulate(tick);
    getLinkComponent(22).get()->simulate(tick);
    nts::Tristate strobe = getLink(1);
    nts::Tristate inhibit = getLink(23);
    nts::Tristate a0 = getLink(2);
    nts::Tristate a1 = getLink(3);
    nts::Tristate a2 = getLink(21);
    nts::Tristate a3 = getLink(22);

    for (auto &pin : _pinToOutput) {
        if (_lastOutputs.find(pin.first) == _lastOutputs.end() && strobe == nts::False) {
            _lastOutputs[pin.first] = nts::Undefined;
            continue;
        }
        if (_lastOutputs.find(pin.first) != _lastOutputs.end() && strobe == nts::False) {
            continue;
        }

        if (inhibit == nts::True && strobe == nts::True) {
            _lastOutputs[pin.first] = nts::False;
            continue;
        }
        if (strobe == nts::Undefined || inhibit == nts::Undefined ||
            a0 == nts::Undefined || a1 == nts::Undefined ||
            a2 == nts::Undefined || a3 == nts::Undefined) {
            _lastOutputs[pin.first] = nts::Undefined;
            continue;
        }
        _lastOutputs[pin.first] = computeDecoder(pin.first);
    }
    _simulating = false;
}

/**
 * @brief compute the decoder of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4514::computeDecoder(size_t outputPin) const
{
    // Get input values from A0-A3 (pins 2,3,21,22)
    nts::Tristate a0 = getLink(2);
    nts::Tristate a1 = getLink(3);
    nts::Tristate a2 = getLink(21);
    nts::Tristate a3 = getLink(22);

    // Convert input pins to binary value
    int value = 0;
    value |= (a0 == nts::True ? 1 : 0);
    value |= (a1 == nts::True ? 2 : 0);
    value |= (a2 == nts::True ? 4 : 0);
    value |= (a3 == nts::True ? 8 : 0);

    auto it = _pinToOutput.find(outputPin);
    return value == it->second ? nts::True : nts::False;
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C4514::computeOutput(std::size_t pin)
{
    // Input pins (return their values)
    if (pin == 1 || pin == 2 || pin == 3 || pin == 21 || pin == 22 || pin == 23)
        return getLink(pin);

    // Power pins
    if (pin == 24 || pin == 12)
        return nts::Tristate::Undefined;

    nts::Tristate strobe = getLink(1);
    nts::Tristate inhibit = getLink(23);
    nts::Tristate a0 = getLink(2);
    nts::Tristate a1 = getLink(3);
    nts::Tristate a2 = getLink(21);
    nts::Tristate a3 = getLink(22);

    if (strobe == nts::False) {
        auto it = _lastOutputs.find(pin);
        return (it != _lastOutputs.end()) ? it->second : nts::Undefined;
    }

    if (inhibit == nts::True && strobe == nts::True)
    return nts::False;

    if (strobe == nts::Undefined || inhibit == nts::Undefined ||
        a0 == nts::Undefined || a1 == nts::Undefined ||
        a2 == nts::Undefined || a3 == nts::Undefined)
        return nts::Undefined;

    // Compute and store new output
    nts::Tristate newOutput = computeDecoder(pin);
    _lastOutputs[pin] = newOutput;
    return newOutput;
}
