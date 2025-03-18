/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** button
*/

#include "button.hpp"
#include <iostream>

Button::Button(std::string path, std::pair<float, float> pos, std::pair<float, float> size, ButtonType type)
{
    if (!_texture.loadFromFile(path))
        throw Error("Failed to load image");
    _sprite.setTexture(_texture);
    if (type == DOOR) {
        _sprite.setTextureRect(sf::IntRect(0,0,72,66));
    } else if (type == AUDIOLOW) {
        _sprite.setTextureRect(sf::IntRect(0,0,78,105));
    } else if (type == AUDIOUP) {
        _sprite.setTextureRect(sf::IntRect(78,0, 78,105));
    } else {
        _sprite.setTextureRect(sf::IntRect(0,0,500,128));
    }
    _type = type;
    _sprite.setPosition((sf::Vector2f) {pos.first, pos.second});
    _sprite.scale((sf::Vector2f) {size.first, size.second});
}
