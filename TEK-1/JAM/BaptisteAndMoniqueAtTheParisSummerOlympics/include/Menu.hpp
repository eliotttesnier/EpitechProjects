/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** Menu
*/

#pragma once
#include <vector>
#include "Button.hpp"
#include "SFML/Audio.hpp"

class Menu {
protected:
    std::vector<Button> _buttons;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Music _buttonSound;

public:
    Menu(const std::string &path);
    ~Menu() = default;

    void draw(sf::RenderWindow &window);
    void handleEvents(sf::Event event);

    void setTexture(std::string &path);
    void setSprite(sf::Sprite sprite);

    std::vector<Button> getButtons();
    sf::Texture getTexture();
    sf::Sprite getSprite();
    sf::Music &getSound();
};
