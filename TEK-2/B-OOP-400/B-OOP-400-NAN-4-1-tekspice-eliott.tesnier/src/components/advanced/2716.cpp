/*
** EPITECH PROJECT, 2025
** NTS
** File description:
** 2716
*/

#include "2716.hpp"

// Constructor

/**
 * @brief Constructor for the 2716 component (ROM)
 */
C2716::C2716()
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
bool C2716::isValidPin(std::size_t pin) const
{
    return (pin >= 1 && pin <= 24 && pin != 12 && pin != 24); // 12, 24 are power
}

/**
 * @brief simulate the logic's component.
 *
 * @param tick The pin checked.
 */
void C2716::simulate(std::size_t tick)
{
    if (tick == _lastTick || _simulating)
        return;
    _simulating = true;
    _lastTick = tick;

    _simulating = false;
}

/**
 * @brief compute the output of the component.
 *
 * @param pin The pin checked.
 *
 * @return nts::Tristate.
 */
nts::Tristate C2716::computeOutput(std::size_t pin)
{
    for (auto &it : _InputToPin) {
        if (it.second == pin) {
            return getLink(pin);
        }
    }

    return nts::Tristate::Undefined;
}
