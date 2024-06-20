/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/action/AbstractAction.hpp"
#include "blocks/movingColor.hpp"

class Lever : public AbstractAction {
    protected:
        MovingColor _color;
    public:
        Lever() = default;
        Lever(sf::Vector2f position, const std::string &texture_path, AbstractMovingPlatform *movingPlatform, MovingColor color);
        Lever(const JsonObject *conf);
        ~Lever() override = default;
        void execute();
};
