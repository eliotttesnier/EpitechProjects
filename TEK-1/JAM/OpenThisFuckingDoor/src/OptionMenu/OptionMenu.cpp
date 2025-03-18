/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** optionMenu
*/

#include "OptionMenu.hpp"
#include "button.hpp"
#include <GameMenu.hpp>
#include "Game.h"
#include <SFML/Audio.hpp>

OptionMenu::OptionMenu()
{
    if (!_optionFont.loadFromFile("assets/font/font.ttf"))
        throw Error("Failed to load font");
    textOptionMenu();
    textAudioMenu();
    textVolumeMenu();
    addButton("assets/OptionMenu/volume_button.png", (std::make_pair<float, float>)((float)game.getWindow().getSize().x / 2 - 250 + 78, (float)500), (std::make_pair<float, float>)((float)1, (float)1), Button::AUDIOLOW);
    addButton("assets/OptionMenu/volume_button.png", (std::make_pair<float, float>)((float)game.getWindow().getSize().x / 2 + 250 - 78 * 2, (float)500), (std::make_pair<float, float>)((float)1, (float)1), Button::AUDIOUP);
}

void OptionMenu::textOptionMenu()
{
    _optionText.setFont(_optionFont);
    _optionText.setString("Option");
    _optionText.setCharacterSize(100);
    _optionText.setFillColor(sf::Color::Yellow);
    _optionText.setStyle(sf::Text::Bold);
    _optionText.setPosition((game.getWindow().getSize().x - _optionText.getGlobalBounds().width) / 2, 50);
}

void OptionMenu::textAudioMenu()
{
    _audioText.setFont(_optionFont);
    _audioText.setString("Audio");
    _audioText.setCharacterSize(75);
    _audioText.setFillColor(sf::Color::Yellow);
    _audioText.setStyle(sf::Text::Bold);
    _audioText.setPosition((game.getWindow().getSize().x - _audioText.getGlobalBounds().width) / 2 - 5 , 375);
}

void OptionMenu::textVolumeMenu()
{
    _volumeText.setFont(_optionFont);
    _volumeText.setString(std::to_string(static_cast<int>(game.getVolumeMenu())));
    _volumeText.setCharacterSize(75);
    _volumeText.setFillColor(sf::Color::Yellow);
    _volumeText.setStyle(sf::Text::Bold);
    _volumeText.setPosition((game.getWindow().getSize().x - _volumeText.getGlobalBounds().width) / 2 - 4, 500);
}

void OptionMenu::displayOptionMenu()
{
    sf::View view;

    view.reset((sf::FloatRect){0, 0, 1920, 1080});
    game.getWindow().setView(view);
    game.getWindow().draw(_optionText);
    game.getWindow().draw(_audioText);
    game.getWindow().draw(_volumeText);
    for (auto& button : _buttons) {
        game.getWindow().draw(*(button->getSprite()));
    }
}

void OptionMenu::addButton(std::string path, std::pair<float, float> pos, std::pair<float, float> size, Button::ButtonType type)
{
    _buttons.push_back(new Button(path, pos, size, type));
}

