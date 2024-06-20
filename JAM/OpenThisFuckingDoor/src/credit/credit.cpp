/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** credit
*/

#include "credit.hpp"
#include "Game.hpp"
#include "Game.h"

Credit::Credit()
{
    if (!_fontText.loadFromFile("assets/font/font.ttf"))
        throw Error("Failed to load font");
    textCreditGroup();
    textCreditSource();
}

void Credit::textCreditGroup()
{
    _textGroup.setFont(_fontText);
    _textGroup.setString("Project group :\n\nNolan Papa - Eliott Tesnier - Noah Auroy\nNathan Bezard - Thomas Boue - Landry Gigant");
    _textGroup.setCharacterSize(60);
    _textGroup.setFillColor(sf::Color::Yellow);
    _textGroup.setStyle(sf::Text::Bold);
    _textGroup.setPosition((game.getWindow().getSize().x - _textGroup.getGlobalBounds().width) / 2, 50);
}

void Credit::textCreditSource()
{
    _textSource.setFont(_fontText);
    _textSource.setString("\nSource :\n   Music name :\n      Autumn-sky-meditation-7618\n   Sprites of button :\n      From vecteezy.com\n   Sprites of player :\n      From Mystic-woods\n   Font :\n      ZOO3 Medium Italic\n   Outil Json :\n      https://github.com/nlohmann/json");
    _textSource.setCharacterSize(50);
    _textSource.setFillColor(sf::Color::Yellow);
    _textSource.setStyle(sf::Text::Bold);
    _textSource.setPosition((game.getWindow().getSize().x - _textSource.getGlobalBounds().width) / 2, 350);
}

void Credit::displayCredit()
{
    sf::View view;

    view.reset((sf::FloatRect){0, 0, 1920, 1080});
    game.getWindow().setView(view);
    game.getWindow().draw(_textGroup);
    game.getWindow().draw(_textSource);
}
