/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** Button
*/

#include "Button.hpp"
#include <iostream>
#include <utility>

Button::Button(const std::string &path, sf::IntRect bounds, const std::function<void()>& fnct, sf::Vector2f position)
{
    _bounds = bounds;
    _texture = sf::Texture();
    _texture.loadFromFile(path);
    _sprite = sf::Sprite(_texture);
    _sprite.setTextureRect(_bounds);
    _sprite.setPosition(position);
    _sprite.setScale({2.0f, 2.0f});
    _state = STATIC;
    _fnct = fnct;
    _position = position;
    _path = path;
}

void Button::draw(sf::RenderWindow &window)
{
    _sprite.setTextureRect(_bounds);
    _sprite.setPosition(_position);
    window.draw(_sprite);
}

void Button::hover()
{
    _state = HOVER;
    _bounds.left = _bounds.width * 1;
}

void Button::noState()
{
    _state = STATIC;
    _bounds.left = 0;
}

void Button::pressed()
{
    _state = PRESS;
    _bounds.left = _bounds.width * 2;
}

void Button::action()
{
    _fnct();
}

bool Button::isOnButton(sf::Vector2f mousePos)
{
    sf::FloatRect rect = _sprite.getGlobalBounds();

    if (mousePos.x < rect.left || mousePos.x > rect.left + rect.width)
        return false;
    if (mousePos.y < rect.top || mousePos.y > rect.top + rect.height)
        return false;
    return true;
}

void Button::setBounds(sf::IntRect bounds)
{
    _bounds = bounds;
}

void Button::setTexture(std::string &path)
{
    _texture.loadFromFile(path);
}

void Button::setSprite(sf::Sprite sprite)
{
    _sprite = std::move(sprite);
}

void Button::setState(Button::State state)
{
    _state = state;
}

void Button::setPosition(sf::Vector2f position)
{
    _position = position;
}

sf::IntRect Button::getBounds()
{
    return _bounds;
}

sf::Texture Button::getTexture()
{
    return _texture;
}

sf::Sprite Button::getSprite()
{
    return _sprite;
}

Button::State Button::getState()
{
    return _state;
}

sf::Vector2f Button::getPosition()
{
    return _position;
}

Button::Button(const Button &other) {
    this->_texture = sf::Texture();
    this->_sprite = sf::Sprite();
    this->_texture.loadFromFile(other._path);
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setScale({2.0f, 2.0f});
    this->_bounds = other._bounds;
    this->_position = other._position;
    this->_fnct = other._fnct;
    this->_path = other._path;
    this->_state = other._state;
}

Button &Button::operator=(const Button &other)
{
    if (this == &other)
        return *this;
    this->_texture = sf::Texture();
    this->_sprite = sf::Sprite();
    this->_texture.loadFromFile(other._path);
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setScale({2.0f, 2.0f});
    this->_bounds = other._bounds;
    this->_position = other._position;
    this->_fnct = other._fnct;
    this->_path = other._path;
    this->_state = other._state;
    return *this;
}
