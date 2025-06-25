/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** main
*/

#include <iostream>

#include "Config/Config.hpp"
#include "Reception/Reception.hpp"
#include "Utils/ReturnValues.hpp"
#include "Utils/ColorUtils.hpp"
#include "Exceptions/Exceptions.hpp"

int main(int ac, char **av)
{
    try {
        Config config = Config::parseArguments(ac, av);
        Reception reception(config);

        reception.run();
    } catch (const Exceptions::CLIParsingException &e) {
        std::cerr << ColorUtils::RED << "Error: " << ColorUtils::RESET
                  << e.what() << std::endl;
        Config::printUsage(av[0]);
        return ReturnValues::FAILURE;
    } catch (const std::exception &e) {
        std::cerr << ColorUtils::RED << "Error: " << ColorUtils::RESET
                  << e.what() << std::endl;
        return ReturnValues::FAILURE;
    }

    return ReturnValues::SUCCESS;
}
