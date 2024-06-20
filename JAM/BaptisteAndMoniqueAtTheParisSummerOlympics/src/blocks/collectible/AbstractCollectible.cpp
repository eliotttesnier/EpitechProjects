/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** AbstractCollectible
*/

#include "blocks/collectible/AbstractCollectible.hpp"

AbstractCollectible::AbstractCollectible(sf::Vector2f position, const std::string &texture_path) : AbstractBlock(position, texture_path)
{
    _hasBeenCollected = false;
}

AbstractCollectible::AbstractCollectible(const JsonObject *object) : AbstractBlock(object)
{
    _hasBeenCollected = false;
}

void AbstractCollectible::setCollected(bool collected)
{
    _hasBeenCollected = collected;
}

bool AbstractCollectible::getCollected() const
{
    return _hasBeenCollected;
}

AbstractCollectible &AbstractCollectible::operator=(const AbstractCollectible &other) {
    if (&other == this)
        return *this;
    AbstractBlock::operator=(other);
    return *this;
}
