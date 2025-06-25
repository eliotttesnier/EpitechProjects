/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** Config
*/

#include <iostream>
#include <cstdlib>
#include <string>

#include "Config.hpp"
#include "../Utils/ColorUtils.hpp"
#include "../Utils/ReturnValues.hpp"
#include "../Exceptions/Exceptions.hpp"

/**
 * @brief Constructor for the Config class
 * @param multiplier The multiplier for cooking time
 * @param cooksPerKitchen The number of cooks per kitchen
 * @param regenerationTimeMs The time in ms to replace ingredients
 */
Config::Config(float multiplier, int cooksPerKitchen, int regenerationTimeMs)
    : _multiplier(multiplier), _cooksPerKitchen(cooksPerKitchen),
    _regenerationTimeMs(regenerationTimeMs)
{
}

/**
 * @brief Get the multiplier for cooking time
 * @return float The multiplier
 */
float Config::getMultiplier() const
{
    return _multiplier;
}

/**
 * @brief Get the number of cooks per kitchen
 * @return int The number of cooks
 */
int Config::getCooksPerKitchen() const
{
    return _cooksPerKitchen;
}

/**
 * @brief Get the regeneration time in milliseconds
 * @return int The regeneration time
 */
int Config::getRegenerationTimeMs() const
{
    return _regenerationTimeMs;
}

/**
 * @brief Print usage message for the program
 * @param programName The name of the program
 */
void Config::printUsage(const std::string &programName)
{
    std::cerr << ColorUtils::BOLD << "USAGE: " << ColorUtils::RESET
              << programName << " <multiplier> <cooks_per_kitchen> <regeneration_time_ms>"
              << std::endl;
    std::cerr << "  - " << ColorUtils::CYAN << "multiplier" << ColorUtils::RESET
              << ": a float >= 0.0 (can be < 1.0 to divide cooking time)" << std::endl;
    std::cerr << "  - " << ColorUtils::CYAN << "cooks_per_kitchen" << ColorUtils::RESET
              << ": a positive integer (>= 1)" << std::endl;
    std::cerr << "  - " << ColorUtils::CYAN << "regeneration_time_ms" << ColorUtils::RESET
              << ": a positive integer (>= 1) in milliseconds" << std::endl;
}

/**
 * @brief Validate the number of arguments
 * @param argc The argument count
 * @param argv The argument values
 */
void Config::validateArguments(int argc, char **argv)
{
    (void)argv;
    if (argc != 4) {
        throw Exceptions::InvalidArgumentCountException();
    }
}

/**
 * @brief Parse and validate the multiplier argument
 * @param arg The multiplier argument string
 * @return float The parsed multiplier value
 */
float Config::parseMultiplier(const std::string &arg)
{
    float multiplier;

    try {
        multiplier = std::stof(arg);
        if (multiplier < 0.0f) {
            throw Exceptions::InvalidMultiplierException(arg);
        }
    } catch (const std::exception &) {
        throw Exceptions::InvalidMultiplierException(arg);
    }

    return multiplier;
}

/**
 * @brief Parse and validate the cooks per kitchen argument
 * @param arg The cooks per kitchen argument string
 * @return int The parsed cooks per kitchen value
 */
int Config::parseCooksPerKitchen(const std::string &arg)
{
    int cooksPerKitchen;

    try {
        cooksPerKitchen = std::stoi(arg);
        if (cooksPerKitchen < 1) {
            throw Exceptions::InvalidCooksException(arg);
        }
    } catch (const std::exception &) {
        throw Exceptions::InvalidCooksException(arg);
    }

    return cooksPerKitchen;
}

/**
 * @brief Parse and validate the regeneration time argument
 * @param arg The regeneration time argument string
 * @return int The parsed regeneration time value
 */
int Config::parseRegenerationTime(const std::string &arg)
{
    int regenerationTimeMs;

    try {
        regenerationTimeMs = std::stoi(arg);
        if (regenerationTimeMs < 1) {
            throw Exceptions::InvalidRegenerationTimeException(arg);
        }
    } catch (const std::exception &) {
        throw Exceptions::InvalidRegenerationTimeException(arg);
    }

    return regenerationTimeMs;
}

/**
 * @brief Parse and validate command line arguments
 * @param argc The argument count
 * @param argv The argument values
 * @return Config The parsed configuration
 */
Config Config::parseArguments(int argc, char **argv)
{
    validateArguments(argc, argv);

    float multiplier = parseMultiplier(argv[1]);
    int cooksPerKitchen = parseCooksPerKitchen(argv[2]);
    int regenerationTimeMs = parseRegenerationTime(argv[3]);

    return Config(multiplier, cooksPerKitchen, regenerationTimeMs);
}
