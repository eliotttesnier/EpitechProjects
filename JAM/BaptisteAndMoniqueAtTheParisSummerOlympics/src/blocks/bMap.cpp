/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/bMap.hpp"

BMap::BMap(sf::Vector2f position, const std::string &texture_path)
    : AbstractPlatform(position, texture_path)
{}

BMap::BMap(const JsonObject *json) : AbstractPlatform(json)
{}

bool BMap::hit(sf::Sprite *sprite)
{
    if (sprite->getGlobalBounds().left  + sprite->getGlobalBounds().width < _sprite.getGlobalBounds().left || sprite->getGlobalBounds().left > _sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width)
        return false;
    else
        return true;
    if (sprite->getGlobalBounds().top < _sprite.getGlobalBounds().top)
        return false;
    else
        return true;
    if (sprite->getGlobalBounds().top > _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height)
        return false;
    if (sprite->getGlobalBounds().left > _sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width)
        return false;
    return true;
    for (std::size_t i = sprite->getGlobalBounds().top; i < sprite->getGlobalBounds().top + sprite->getGlobalBounds().height + 10.0f; i++) {
        for (std::size_t j = sprite->getGlobalBounds().left; j < sprite->getGlobalBounds().left + sprite->getGlobalBounds().width + 10.0f; j++) {
            if (_sprite.getGlobalBounds().contains(j, i))
                return true;
        }
    }
    return false;
}

BMap &BMap::operator=(const BMap &other)
{
    if (&other == this)
        return *this;
    AbstractPlatform::operator=(other);
    return *this;
}
