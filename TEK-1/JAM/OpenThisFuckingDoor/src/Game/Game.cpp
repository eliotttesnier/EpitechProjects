/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Game
*/

#include "Game.hpp"
#include "button.hpp"
#include "Game.h"
#include <cmath>
#include "credit.hpp"


void Game::displayFilter(void)
{
    sf::Texture texture;
    sf::Sprite sprite;
    if (game.getTimeLine() == GameMap::TimeLine::PAST) {
        texture.loadFromFile("assets/past.png");
        sprite.setTexture(texture);
        sprite.setPosition(0,0);
        sprite.setScale(10,10);
        sprite.setOrigin(-10,-10);
        game.getWindow().draw(sprite);
    }
    if (game.getTimeLine() == GameMap::TimeLine::FUTUR) {
        texture.loadFromFile("assets/futur.png");
        sprite.setTexture(texture);
        sprite.setPosition(0,0);
        sprite.setScale(10,10);
        sprite.setOrigin(-10,-10);
        game.getWindow().draw(sprite);
    }
}

Game::Game()
{
    _gameMap = new GameMap();
    _timeLine = GameMap::TimeLine::PRESENT;
    _gameMap->setupMap("assets/mapConfig/mapPresent.json", GameMap::BACKGROUND, GameMap::TimeLine::PAST);
    _gameMap->setupMap("assets/mapConfig/colPresent.json", GameMap::HITBOX, GameMap::TimeLine::PAST);
    _gameMap->setupMap("assets/mapConfig/mapPresent.json", GameMap::BACKGROUND, GameMap::TimeLine::PRESENT);
    _gameMap->setupMap("assets/mapConfig/colPresent.json", GameMap::HITBOX, GameMap::TimeLine::PRESENT);
    _gameMap->setupMap("assets/mapConfig/mapFutur.json", GameMap::BACKGROUND, GameMap::TimeLine::FUTUR);
    _gameMap->setupMap("assets/mapConfig/colFutur.json", GameMap::HITBOX, GameMap::TimeLine::FUTUR);
    _window.create(sf::VideoMode(1920, 1080), "OpenThisFuckingDoor", sf::Style::Close | sf::Style::Fullscreen);
    if (!isWindowOpen())
        throw Error("Failed to create window");
    _event = sf::Event();
    if (!_musicGame.openFromFile("assets/music/music_gameplay.wav"))
        throw Error("Failed to load Music");
    _musicGame.setLoop(true);
    _GameMenu = new GameMenu();
    _OptionMenu = new OptionMenu();
    _scene = GAMEMENU;
    _credit = new Credit();
    sf::FloatRect rect = sf::FloatRect(0, 0, 1920, 1080);
    _view = new sf::View(rect);
    game.getWindow().setView(*_view);
    _player = new Player("assets/character/player/idle/idle_1.png", std::pair<int, int>(4922, 5575), std::pair<int, int>(13, 22));
}

Game::~Game()
{
    closeWindow();
}

bool Game::isWindowOpen() const
{
    return _window.isOpen();
}

void Game::closeWindow()
{
    _window.close();
    if (isWindowOpen())
        throw Error("Failed to close window");
}

void Game::clearWindow()
{
    _window.clear();
}

int Game::getKeyEvent()
{
    static bool state = false;

    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::KeyPressed)
            for (auto& binds : _keyFunctions) {
                if (binds.first == _event.key.code) {
                    binds.second();
                }
            }
        if (_event.type == sf::Event::MouseButtonPressed) {
            state = true;
            handleMousePress();
        }
        if (_event.type == sf::Event::MouseButtonReleased) {
            state = false;
            handleMouseReleased();
        }
        if (_event.type == sf::Event::MouseMoved && state != true)
            handleMouseOver();
        if (game.getScene() == GAMEPLAY) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                game.getPlayer()->data["direction"] = UP;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                game.getPlayer()->data["direction"] = DOWN;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                game.getPlayer()->data["interacting"] = true;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                game.getPlayer()->data["direction"] = RIGHT;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                game.getPlayer()->data["direction"] = LEFT;
            else
                game.getPlayer()->data["direction"] = IDLE;
        }
    }
    return -1;
}

void Game::handleMouseOver()
{
    sf::Vector2f mousePos = game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow()));
    sf::IntRect rect;

    for (auto& button :game.getGameMenu()->getbutton()) {
        if (_scene == GAMEMENU) {
            if (button->getSprite()->getGlobalBounds().contains(mousePos)) {
                if (button->getType() == button->DOOR) {
                    rect = sf::IntRect(72,0,72,66);
                    button->getSprite()->setTextureRect(rect);
                } else {
                    rect = sf::IntRect(0,133,500,133);
                    button->getSprite()->setTextureRect(rect);
                }
            } else {
                if (button->getType() == button->DOOR) {
                    rect = sf::IntRect(0,0,72,66);
                    button->getSprite()->setTextureRect(rect);
                } else {
                    rect = sf::IntRect(0,0,500,128);
                    button->getSprite()->setTextureRect(rect);
                }
            }
        }
    }
    for (auto& button :game.getOptionMenu()->getbutton()) {
        if (_scene == OPTION) {
            if (button->getSprite()->getGlobalBounds().contains(mousePos)) {
                if (button->getType() == button->AUDIOLOW) {
                    rect = sf::IntRect(0,105,78,105);
                    button->getSprite()->setTextureRect(rect);
                } else if (button->getType() == button->AUDIOUP) {
                    rect = sf::IntRect(78,105, 78,105);
                    button->getSprite()->setTextureRect(rect);
                }
            } else {
                if (button->getType() == button->AUDIOLOW) {
                    rect = sf::IntRect(0,0,78,105);
                    button->getSprite()->setTextureRect(rect);
                } else if (button->getType() == button->AUDIOUP) {
                    rect = sf::IntRect(78,0, 78,105);
                    button->getSprite()->setTextureRect(rect);
                }
            }
        }
    }
}

void Game::handleMousePress()
{
    sf::Vector2f mousePos = game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow()));
    sf::IntRect rect;

    for (auto& button :game.getGameMenu()->getbutton()) {
        if (button->getSprite()->getGlobalBounds().contains(mousePos)) {
            if (_scene == GAMEMENU) {
                if (button->getType() == button->DOOR) {
                    rect = sf::IntRect(144,0,72,66);
                    button->getSprite()->setTextureRect(rect);
                    rect = sf::IntRect(216,0,72,66);
                    button->getSprite()->setTextureRect(rect);
                } else {
                    rect = sf::IntRect(0,266,500,133);
                    button->getSprite()->setTextureRect(rect);
                }
            }
        }
    }
    for (auto& button :game.getOptionMenu()->getbutton()) {
        if (_scene == OPTION) {
            if (button->getSprite()->getGlobalBounds().contains(mousePos)) {
                if (button->getType() == button->AUDIOLOW) {
                    rect = sf::IntRect(0,210,78,105);
                    button->getSprite()->setTextureRect(rect);
                    if (round(game.getVolumeMenu()) > 0.00) {
                        game.setGameVolume(round(game.getVolumeMenu() - 5.00));
                        game.getOptionMenu()->getTextVolume()->setString(std::to_string((int)round(game.getVolumeMenu())));
                    }
                } else if (button->getType() == button->AUDIOUP) {
                    rect = sf::IntRect(78,210, 78,105);
                    button->getSprite()->setTextureRect(rect);
                    if (round(game.getVolumeMenu()) < 100) {
                        game.setGameVolume(round(game.getVolumeMenu() + 5.00));
                        game.getOptionMenu()->getTextVolume()->setString(std::to_string((int)round(game.getVolumeMenu())));
                    }
                }
            }
        }
    }
}

void Game::handleMouseReleased()
{
    sf::Vector2f mousePos = game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow()));
    sf::IntRect rect;

    for (auto& button :game.getGameMenu()->getbutton()) {
        if (_scene == GAMEMENU) {
            if (button->getType() == button->DOOR) {
                rect = sf::IntRect(0,0,72,66);
                button->getSprite()->setTextureRect(rect);
            } else {
                rect = sf::IntRect(0,0,500,128);
                button->getSprite()->setTextureRect(rect);
            }
            if (button->getSprite()->getGlobalBounds().contains(mousePos)) {
                if (button->getType() == button->LEAVE) {
                    closeWindow();
                }
                if (button->getType() == button->DOOR) {
                    setScene(GAMEPLAY);
                }
                if (button->getType() == button->OPTION) {
                    setScene(OPTION);
                }
                if (button->getType() == button->CREDIT) {
                    setScene(CREDIT);
                }
            }
        }
    }
    for (auto& button :game.getOptionMenu()->getbutton()) {
        if (_scene == OPTION) {
            if (button->getType() == button->AUDIOLOW) {
                rect = sf::IntRect(0,0,78,105);
                button->getSprite()->setTextureRect(rect);
            } else if (button->getType() == button->AUDIOUP) {
                rect = sf::IntRect(78,0, 78,105);
                button->getSprite()->setTextureRect(rect);
            }
        }
    }
}

void Game::DisplayWindow()
{
    _window.display();
}

void Game::setTotem(int totem)
{
    std::pair<Map, Map> map = _gameMap->getMap(_timeLine);
    for (auto& row : map.second) {
        for (auto& obj : row) {
            // finds if the object has the data "pillar"
            if (obj->data.find("pillar") != obj->data.end()) {
                // if the object has the data "pillar" and the data "totem" is equal to the totem
                if (std::any_cast<int>(obj->data["pillar"]) == totem) {
                    // change the texture of the object
                    sf::Texture texture;
                    texture.loadFromFile("./assets/totem_pillar/pillar_finished.png");
                    obj->data["sfTexture"] = texture;
                    obj->data["texture"] = "./assets/totem_pillar/pillar_finished.png";
                }
            }
        }
    }
}

void Game::getTotem()
{
    std::pair<Map, Map> map = _gameMap->getMap(_timeLine);
    for (auto& row : map.second) {
        for (auto& obj : row) {
            if (obj->data.find("isTotem") != obj->data.end()) {
                if (std::any_cast<int>(obj->data["totem"]) == 1) {
                    sf::Texture texture;
                    texture.loadFromFile("./assets/thomas.png");
                    obj->data["sfTexture"] = texture;
                    obj->data["texture"] = "./assets/thomas.png";
                }
            }
        }
    }
}

void Game::playMusic()
{
    _musicGame.setVolume(100.0);
    _musicGame.play();
}
