/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Level.hpp"
#include "Player.hpp"
#include "Menu.hpp"
#include <SFML/Audio.hpp>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class Game {
protected:
    sf::RenderWindow _window;
    Level *_currentLevel;
    std::vector<Level *> _levels;
    std::size_t _currentLevelIndex;
    bool _isRunning;
    Player *_player1;
    Player *_player2;
    Menu *_menu;
    bool _inMenu;
    sf::Music _music;
    float _volume;

public:
    Game(const std::string &levelsDir, const BlockFactory &blockFactory);
    ~Game();

    void openWindow();
    void run();
    void stop();

    void loadLevel(std::size_t index);

    void handleEvents();
    void update();
    void render();

    bool isRunning() const;
    Level *getCurrentLevel() const;
    std::vector<Level *> getLevels() const;
    std::size_t getCurrentLevelIndex() const;
    [[nodiscard]] Player *getPlayer1() const;
    [[nodiscard]] Player *getPlayer2() const;
    [[nodiscard]] std::vector<Player *> getPlayers() const;
    bool getInMenu() const;

    void setCurrentLevel(Level *level);
    void setLevels(const std::vector<Level *> &levels);
    void setInMenu(bool inMenu);
    void setVolume(float volume);

    sf::RenderWindow &getWindow();
    float getVolume();
    sf::Music &getMusic();
    Menu *getMenu();
};

extern Game *currentGame;
