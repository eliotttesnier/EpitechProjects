/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Game.hpp"

void playButton()
{
    currentGame->setInMenu(false);
}

void restartButton()
{
    currentGame->getCurrentLevel()->reset();
    currentGame->setInMenu(false);
}

void quitButton()
{
    currentGame->getWindow().close();
}

void volDownButton()
{
    float vol = currentGame->getVolume();

    vol -= 10;
    if (vol <= 0)
        vol = 0;
    currentGame->setVolume(vol);
    currentGame->getMusic().setVolume(vol);
    currentGame->getMenu()->getSound().setVolume(vol);
}

void volUpButton()
{
    float vol = currentGame->getVolume();

    vol += 10;
    if (vol >= 100)
        vol = 100;
    currentGame->setVolume(vol);
    currentGame->getMusic().setVolume(vol);
    currentGame->getMenu()->getSound().setVolume(vol);
}

Menu::Menu(const std::string &path)
{
    Button play = Button("assets/buttons/play.png", {0, 0, 144, 72}, playButton, {796, 700});
    Button restart = Button("assets/buttons/restart.png", {0, 0, 144, 72}, restartButton, {996, 550});
    Button quit = Button("assets/buttons/quit.png", {0, 0, 144, 72}, quitButton, {596, 550});
    Button volUp = Button("assets/buttons/volUp.png", {0, 0, 16, 16}, volUpButton, {350, 825});
    Button volDown = Button("assets/buttons/volDown.png", {0, 0, 16, 16}, volDownButton, {400, 825});

    _texture = sf::Texture();
    _texture.loadFromFile(path);
    _sprite = sf::Sprite(_texture);
    _buttons.push_back(play);
    _buttons.push_back(restart);
    _buttons.push_back(quit);
    _buttons.push_back(volUp);
    _buttons.push_back(volDown);
    _buttonSound.openFromFile("assets/musique/button.wav");
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
    for (auto &button : _buttons) {
        button.draw(window);
    }
}

void Menu::handleEvents(sf::Event event)
{
    if (event.type == sf::Event::MouseMoved) {
        for (auto &button : _buttons) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                break;
            if (button.isOnButton({static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)})
                && button.getState() != Button::PRESS)
                button.hover();
            else if (button.getState() != Button::PRESS)
                button.noState();
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto &button : _buttons) {
            if (button.getState() == Button::HOVER)
                button.pressed();
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        for (auto &button : _buttons) {
            if (button.getState() == Button::PRESS) {
                button.hover();
                button.action();
                _buttonSound.stop();
                _buttonSound.play();
            }
        }
    }
}

void Menu::setTexture(std::string &path)
{
    _texture.loadFromFile(path);
}

void Menu::setSprite(sf::Sprite sprite)
{
    _sprite = sprite;
}

std::vector<Button> Menu::getButtons()
{
    return _buttons;
}

sf::Texture Menu::getTexture()
{
    return _texture;
}

sf::Sprite Menu::getSprite()
{
    return _sprite;
}

sf::Music &Menu::getSound()
{
    return _buttonSound;
}