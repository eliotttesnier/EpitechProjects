/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-tekspice-eliott.tesnier
** File description:
** Logger
*/

#include "Logger.hpp"
#include <fstream>

// Constructor

/**
 * @brief Constructor for the Logger component
 */
Logger::Logger()
{
    _nbPins = 10;
    _inputs.resize(8, nts::Undefined);
}

// Method

/**
 * @brief Check if the pin is valid for the component.
 *
 * @param pin The pin checked.
 *
 * @return bool.
 */
bool Logger::isValidPin(std::size_t pin) const
{
    return pin >= 1 && pin <= 10;
}

/**
 * @brief simulate the logic's component.
 *
 * @param tick The pin checked.
 */
void Logger::simulate(std::size_t tick)
{
    if (tick == _lastTick || _simulating)
        return;
    _lastTick = tick;
    _simulating = true;

    getLinkComponent(_clockPin)->simulate(tick);

    for (std::size_t i = 0; i < 8; ++i) {
        getLinkComponent(i + 1)->simulate(tick);
    }

    nts::Tristate clock = getLink(_clockPin);

    if (_lastClock == nts::False && clock == nts::True) {
        _risingEdge = true;
    } else {
        _risingEdge = false;
    }
    _lastClock = clock;
    if (!_risingEdge || getLink(_inhibitPin) == nts::Tristate::True) {
        _simulating = false;
        return;
    }
    uint8_t byte = 0;
    for (std::size_t i = 0; i < 8; ++i) {
        nts::Tristate state = getLink(i + 1);
        if (state == nts::Tristate::Undefined) {
            _simulating = false;
            return;
        }
        byte |= (state == nts::Tristate::True) << i;
    }

    std::ofstream logFile("log.bin", std::ios::binary | std::ios::app);
    if (logFile.is_open()) {
        logFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
        logFile.close();
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
nts::Tristate Logger::computeOutput(std::size_t pin)
{
    return getLink(pin);
}
