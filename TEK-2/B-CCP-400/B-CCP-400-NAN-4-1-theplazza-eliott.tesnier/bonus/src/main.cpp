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
#include "Pizza/PizzaConfig.hpp"

#ifdef GUI_ENABLED
#include "GUI/GuiApplication.hpp"
#include "GUI/ReceptionGUI.hpp"
#endif

int main(int ac, char **av)
{
    try {
        auto& pizzaConfig = Pizza::PizzaConfig::getInstance();
        pizzaConfig.loadPizzasFromJson("config/pizzas.json");
        pizzaConfig.loadIngredientsFromJson("config/ingredients.json");

        std::cout << ColorUtils::GREEN << "✓ Pizza configuration loaded successfully" << ColorUtils::RESET << std::endl;

        Config config = Config::parseArguments(ac, av);

#ifdef GUI_ENABLED
        if (config.useGui()) {
            GuiApplication app(ac, av);
            ReceptionGUI *receptionGUI = new ReceptionGUI();
            receptionGUI->setConfig(config);
            receptionGUI->show();
            return app.exec();
        }
#else
        if (config.useGui()) {
            std::cerr << ColorUtils::RED << "Error: " << ColorUtils::RESET
                      << "GUI support not compiled. Please rebuild with Qt support." << std::endl;
            return ReturnValues::FAILURE;
        }
#endif

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
