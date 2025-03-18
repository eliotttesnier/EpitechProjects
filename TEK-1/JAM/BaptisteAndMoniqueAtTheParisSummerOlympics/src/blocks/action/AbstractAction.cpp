/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/action/AbstractAction.hpp"

AbstractAction::AbstractAction(sf::Vector2f position, const std::string &texture_path, AbstractMovingPlatform *movingPlatform) : AbstractBlock(position, texture_path)
{
    _movingPlatform = movingPlatform;
}

AbstractAction::AbstractAction(const JsonObject *conf) : AbstractBlock(conf)
{
    _movingPlatform = nullptr;
}
