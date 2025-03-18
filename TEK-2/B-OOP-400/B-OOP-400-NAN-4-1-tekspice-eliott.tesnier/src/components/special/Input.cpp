/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Input
*/

#include "Input.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component Input.
 */
Input::Input()
{
    _nbPins = 1;
    _state = nts::Tristate::Undefined;
    _previousState = nts::Tristate::Undefined;
    _actualised = false;
}

//Method

/**
 * @brief Simulate the component.
 *
 * @param tick the tick at this moment
 */
void Input::simulate(std::size_t tick)
{
    if (tick == _lastTick)
        return;
    _lastTick = tick;

    _actualised = true;
}

//Setter

/**
 * @brief Set the state of the component.
 *
 * @param state the state of the component.
 */
void Input::setState(nts::Tristate state)
{
    _actualised = false;
    _previousState = _state;
    _state = state;
}

/**
 * @brief Check the pin of the component.
 *
 * @param pin the pin checked
 *
 * @return bool.
 */
bool Input::isValidPin(std::size_t pin) const
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
nts::Tristate Input::computeOutput(std::size_t pin)
{
    (void)pin;
    return _actualised ? _state : _previousState;
}
