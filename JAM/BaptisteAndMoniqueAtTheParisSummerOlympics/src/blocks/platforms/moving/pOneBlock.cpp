/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/platforms/moving/pOneBlock.hpp"

POneBlock::POneBlock(sf::Vector2f start_pos, sf::Vector2f end_pos, float speed, const std::string &texture_path, MovingColor color)
    : AbstractMovingPlatform(start_pos, end_pos, speed, texture_path)
{
    _color = color;
}

POneBlock::POneBlock(const JsonObject *conf)
    : AbstractMovingPlatform(conf)
{}

bool POneBlock::hit(sf::Sprite *sprite)
{
    for (std::size_t i = sprite->getGlobalBounds().top; i < sprite->getGlobalBounds().top + sprite->getGlobalBounds().height; i++) {
        for (std::size_t j = sprite->getGlobalBounds().left; j < sprite->getGlobalBounds().left + sprite->getGlobalBounds().width; j++) {
            if (_sprite.getGlobalBounds().contains(j, i))
                return true;
        }
    }
    return false;
}
