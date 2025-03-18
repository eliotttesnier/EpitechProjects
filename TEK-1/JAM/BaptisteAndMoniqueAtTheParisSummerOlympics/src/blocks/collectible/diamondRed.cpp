/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/collectible/diamondRed.hpp"

DiamondRed::DiamondRed() : AbstractCollectible(sf::Vector2f{0, 0}, "")
{
}

DiamondRed::DiamondRed(sf::Vector2f position, const std::string &texture_path) : AbstractCollectible(position, texture_path)
{
}

DiamondRed::DiamondRed(const JsonObject *object) : AbstractCollectible(object)
{
}
