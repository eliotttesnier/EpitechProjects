/*
** EPITECH PROJECT, 2025
** tekspice
** File description:
** Output
*/

#include "Output.hpp"
#include "Error.hpp"

// Constructor

/**
 * @brief Constructor for the component OutPut.
 */
Output::Output()
{
    _nbPins = 1;
}

//Method

/**
 * @brief Check the pin of the component.
 *
 * @param pin the pin checked
 *
 * @return bool.
 */
bool Output::isValidPin(std::size_t pin) const
{
    return pin == 1;
}

/**
 * @brief check the output of the component.
 *
 * @param pin the pin checked
 *
 * @return nst::Tristate.
 */
nts::Tristate Output::computeOutput(std::size_t pin)
{
    auto it = _links.find(pin);

    if (it == _links.end())
        throw nts::InvalidArgument("Output: No connection on pin " + std::to_string(pin));
    return it->second.first->compute(it->second.second);
}
