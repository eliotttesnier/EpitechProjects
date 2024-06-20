/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <iostream>
#include <filesystem>
#include "Game.hpp"
#include <unistd.h>

Game::Game(const std::string &levelsDir, const BlockFactory &blockFactory)
{
    for (const auto & entry : std::filesystem::directory_iterator(levelsDir)) {
        if (entry.path().extension() == ".json") {
            std::cout << "Loading lvl: " << entry.path() << std::endl;
            auto *lvl = new Level(entry.path(), blockFactory);
            _levels.push_back(lvl);
        }
    }
    if (_levels.empty()) {
        std::cerr << "No levels found in " << levelsDir << std::endl;
        exit(84);
    }
    _currentLevel = _levels[0];
    _currentLevelIndex = 0;
    _isRunning = false;
    _player1 = new Player();
    _player2 = new Player(1);
    _player1->getPosition().x = _currentLevel->getStartPosP1().x;
    _player1->getPosition().y = _currentLevel->getStartPosP1().y;
    _player2->getPosition().x = _currentLevel->getStartPosP2().x;
    _player2->getPosition().y = _currentLevel->getStartPosP2().y;
    _menu = new Menu("assets/buttons/menu.png");
    _inMenu = true;
    _music.openFromFile("assets/musique/musique.wav");
    _music.setLoop(true);
    _music.play();
    _volume = 100;
}

Game::~Game()
{
    stop();
}

void Game::openWindow()
{
    std::cout << "Opening window..." << std::endl;
    _window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BaptisteAndMoniqueAtTheParisSummerOlympics");
    if (_window.isOpen()) {
        std::cout << "Window successfully opened!" << std::endl;
    } else {
        std::cout << "Failed to open window!" << std::endl;
    }
}

void Game::run()
{
    openWindow();
    _isRunning = true;
    while (isRunning()) {
        handleEvents();
        update();
        render();
        _currentLevel->update();
        usleep(100);
    }
    _window.close();
}

void Game::stop()
{
    _isRunning = false;
}

void Game::handleEvents()
{
    sf::Event event{};

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            _inMenu = !_inMenu;
        if (_inMenu)
            _menu->handleEvents(event);
    }
    if (_inMenu)
        return;
    if (sf::Joystick::isConnected(0)) { // Manette 1
        if (sf::Joystick::isButtonPressed(0, 0)) // Bouton A
            _player1->jump();
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -25) // gauche
            _player1->left();
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 25) // droite
            _player1->right();
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            _player1->jump();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            _player1->left();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            _player1->right();
    }

    if (sf::Joystick::isConnected(1)) { // Manette 2
        if (sf::Joystick::isButtonPressed(1, 0)) // Bouton A
            _player2->jump();
        if (sf::Joystick::getAxisPosition(1, sf::Joystick::X) < -25) // gauche
            _player2->left();
        if (sf::Joystick::getAxisPosition(1, sf::Joystick::X) > 25) // droite
            _player2->right();
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            _player2->jump();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            _player2->left();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _player2->right();
    }
}

void Game::update()
{
    if (!_inMenu) {
        _player1->anim();
        _player1->update();
        _player2->anim();
        _player2->update();
    }
    _window.clear(sf::Color::White);
}

void Game::render()
{
    _currentLevel->draw(&_window);
    // _player1->draw(_window);
    // _player2->draw(_window);
    if (_inMenu)
        _menu->draw(_window);
    _window.display();
}

bool Game::isRunning() const
{
    if (_window.isOpen() && _isRunning)
        return true;
    return false;
}

sf::RenderWindow &Game::getWindow()
{
    return _window;
}

Menu *Game::getMenu()
{
    return _menu;
}

void Game::loadLevel(std::size_t index)
{
    if (index < 0 || index >= _levels.size())
        throw std::out_of_range("Level index out of range");
    _currentLevel = _levels[index];
    _currentLevelIndex = index;
}

Level *Game::getCurrentLevel() const
{
    return _currentLevel;
}

std::vector<Level *> Game::getLevels() const
{
    return _levels;
}

std::size_t Game::getCurrentLevelIndex() const
{
    return _currentLevelIndex;
}

Player *Game::getPlayer1() const
{
    return _player1;
}

Player *Game::getPlayer2() const
{
    return _player2;
}

std::vector<Player *> Game::getPlayers() const
{
    return {_player1, _player2};
}

void Game::setVolume(float volume)
{
    _volume = volume;
}

float Game::getVolume()
{
    return _volume;
}

sf::Music &Game::getMusic()
{
    return _music;
}

bool Game::getInMenu() const
{
    return _inMenu;
}

void Game::setCurrentLevel(Level *level)
{
    _currentLevel = level;
}

void Game::setLevels(const std::vector<Level *> &levels)
{
    _levels = levels;
}

void Game::setInMenu(bool inMenu)
{
    _inMenu = inMenu;
}
