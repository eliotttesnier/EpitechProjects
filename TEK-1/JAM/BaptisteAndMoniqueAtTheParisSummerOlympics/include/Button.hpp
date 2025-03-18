/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** Button
*/

#pragma once
#include <functional>
#include "SFML/Graphics.hpp"
#include <string>


class Button {
public:
    enum State {
        STATIC = 0,
        HOVER,
        PRESS
    };
protected:
    sf::IntRect _bounds;
    sf::Texture _texture;
    sf::Sprite _sprite;
    Button::State _state;
    std::function<void()> _fnct;
    sf::Vector2f _position;
    std::string _path;

public:
    Button(const std::string &path, sf::IntRect bounds, const std::function<void()>& fnct, sf::Vector2f position);
    Button(const Button &button);
    ~Button() = default;

    void draw(sf::RenderWindow &window);
    void noState();
    void hover();
    void pressed();
    void action();
    bool isOnButton(sf::Vector2f mousePos);

    void setBounds(sf::IntRect bounds);
    void setTexture(std::string &path);
    void setSprite(sf::Sprite sprite);
    void setState(Button::State state);
    void setPosition(sf::Vector2f position);

    sf::IntRect getBounds();
    sf::Texture getTexture();
    sf::Sprite getSprite();
    Button::State getState();
    sf::Vector2f getPosition();


    Button &operator=(const Button& other);
};

