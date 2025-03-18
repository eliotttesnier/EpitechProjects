/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Clock
*/

#include "Clock.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component Clock.
 */
Clock::Clock()
{
    _nbPins = 0;
    _state = nts::Tristate::Undefined;
    _previousState = nts::Tristate::Undefined;
    _actualised = false;
}

//Method

/**
 * @brief Set the state of the clock component.
 *
 * @param state the state to set
 */
void Clock::setState(nts::Tristate state)
{
    _actualised = false;
    _previousState = _state;
    _state = state;
}

/**
 * @brief Simulate the component.
 *
 * @param tick the tick at this moment
 */
void Clock::simulate(std::size_t tick)
{
    if (tick == _lastTick)
        return;
    _lastTick = tick;

    if (!_actualised) {
        _actualised = true;
        return;
    }

    if (_state == nts::Tristate::True)
        _state = nts::Tristate::False;
    else if (_state == nts::Tristate::False)
        _state = nts::Tristate::True;
}

/**
 * @brief Check the pin of the component.
 *
 * @param pin the pin checked
 *
 * @return bool.
 */
bool Clock::isValidPin(std::size_t pin) const
{
    return pin == 1;
}

/**
 * @brief check the intput of the component.
 *
 * @param pin the pin checked
 *
 * @return nst::Tristate.
 */
nts::Tristate Clock::computeOutput(std::size_t pin)
{
    (void)pin;
    return _actualised ? _state : _previousState;
}
