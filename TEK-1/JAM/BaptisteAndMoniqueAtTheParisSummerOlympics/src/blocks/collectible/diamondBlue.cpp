/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/collectible/diamondBlue.hpp"

DiamondBlue::DiamondBlue() : AbstractCollectible(sf::Vector2f{0, 0}, "")
{
}

DiamondBlue::DiamondBlue(sf::Vector2f position, const std::string &texture_path) : AbstractCollectible(position, texture_path)
{
}

DiamondBlue::DiamondBlue(const JsonObject *object) : AbstractCollectible(object)
{
}
