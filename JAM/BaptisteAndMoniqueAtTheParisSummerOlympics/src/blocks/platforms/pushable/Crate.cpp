/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/platforms/pushable/Crate.hpp"
#include "Game.hpp"

Crate::Crate(sf::Vector2f position, const std::string &texture_path) : AbstractPushable(position, texture_path)
{
}

Crate::Crate(const JsonObject *conf) : AbstractPushable(conf)
{
}

bool Crate::hit(sf::Sprite *sprite)
{
    for (std::size_t i = sprite->getGlobalBounds().top; i < sprite->getGlobalBounds().top + sprite->getGlobalBounds().height; i++) {
        for (std::size_t j = sprite->getGlobalBounds().left; j < sprite->getGlobalBounds().left + sprite->getGlobalBounds().width; j++) {
            sf::Vector2f position = {static_cast<float>(j), static_cast<float>(i)};
            if (_sprite.getGlobalBounds().contains(position)) {
                for (std::size_t i = 0; currentGame->getCurrentLevel()->getBlocks()[i] != nullptr; i++) {
                    if (!_sprite.getGlobalBounds().contains(currentGame->getCurrentLevel()->getBlocks()[i]->getPosition())) {
                        if (_position.y < position.y || position.y > position.y)
                            return false;
                        if (position.x < _position.x) {
                            _position.x += 0.01f;
                        } else {
                            _position.x -= 0.01f;
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}
