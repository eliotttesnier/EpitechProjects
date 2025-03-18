/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "json/Json.hpp"

class AbstractBlock {
protected:
    sf::Vector2f _position;
    sf::Texture _texture;
    sf::Sprite _sprite;

    AbstractBlock(sf::Vector2f position, const std::string &texture_path);
    AbstractBlock(const JsonObject *object);
public:
    std::string _texture_path;
    AbstractBlock(const AbstractBlock &other) = default;
    virtual ~AbstractBlock() = default;

    // ---------- Methods ----------
    virtual void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition();

    // ---------- Operator Overloads ----------
    AbstractBlock &operator=(const AbstractBlock &other);
};
