/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/action/Lever.hpp"
#include <iostream>
#include "Game.hpp"

Lever::Lever(sf::Vector2f position, const std::string &texture_path, AbstractMovingPlatform *movingPlatform, MovingColor color)
    : AbstractAction(position, texture_path, movingPlatform)
{
    _color = color;
}

Lever::Lever(const JsonObject *conf)
    : AbstractAction(conf)
{
    JsonObject *data = conf->getValue<JsonObject>("data");
    try {
        if (data->getString("color") == "red") {
            _color = MovingColor::RED;
        } else if (data->getString("color") == "blue") {
            _color = MovingColor::BLUE;
        } else if (data->getString("color") == "green") {
            _color = MovingColor::GREEN;
        } else if (data->getString("color") == "yellow") {
            _color = MovingColor::YELLOW;
        } else if (data->getString("color") == "purple") {
            _color = MovingColor::PURPLE;
        } else if (data->getString("color") == "white") {
            _color = MovingColor::WHITE;
        } else {
            std::cerr << "Error: invalid color" << std::endl;
            exit(84);
        }
    } catch (std::exception &e) {
        std::cerr << "Error: missing coolor" << std::endl;
        exit(84);
    }
    if (currentGame == nullptr || currentGame->getCurrentLevel() == nullptr) {
        return;
    }
    for (std::size_t i = 0; currentGame->getCurrentLevel()->getBlocks()[i] != nullptr; i++) {
        try {
            auto movingPlatform = dynamic_cast<AbstractMovingPlatform *>(currentGame->getCurrentLevel()->getBlocks()[i]);
            if (movingPlatform != nullptr && movingPlatform->getColor() == _color) {
                _movingPlatform = movingPlatform;
                break;
            }
        } catch (std::bad_cast &e) {
            continue;
        }
    }
}

void Lever::execute()
{
    _movingPlatform->setShouldMove(!_movingPlatform->getShouldMove());
}
