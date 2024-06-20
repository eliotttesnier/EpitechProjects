/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "blocks/AbstractBlock.hpp"

AbstractBlock::AbstractBlock(sf::Vector2f position, const std::string &texture_path)
{
    _position = position;
    _texture = sf::Texture();
    _texture.loadFromFile(texture_path);
    _sprite = sf::Sprite(_texture);
}

AbstractBlock::AbstractBlock(const JsonObject *object)
{
    _position = {static_cast<float>(object->getValue<JsonObject>("pos")->getFloat("x") * 33.0f), static_cast<float>(object->getValue<JsonObject>("pos")->getFloat("y") * 33.0f)};
    _texture = sf::Texture();
    _texture_path = object->getString("texture");
    _texture.loadFromFile(_texture_path);
    _sprite = sf::Sprite(_texture);
    _sprite.setPosition(_position);
}

void AbstractBlock::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

void AbstractBlock::setPosition(sf::Vector2f position)
{
    _position = position;
}

sf::Vector2f AbstractBlock::getPosition()
{
    return _position;
}

AbstractBlock &AbstractBlock::operator=(const AbstractBlock &other) {
    if (&other == this)
        return *this;
    _position = other._position;
    _texture = other._texture;
    _sprite = other._sprite;
    return *this;
}
