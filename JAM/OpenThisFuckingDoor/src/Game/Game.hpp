/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Game
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <functional>
#include "../GameMenu/GameMenu.hpp"
#include "../Player/Player.hpp"
#include "OptionMenu.hpp"
#include "credit.hpp"
#include "GameMap.hpp"

enum Scene {
    GAMEMENU = 0,
    OPTION = 1,
    CREDIT = 2,
    GAMEPLAY = 3,
};

class Game {
    public:
        Game();
        ~Game();

        //Window
        bool isWindowOpen() const;
        void closeWindow();
        void clearWindow();

        //Events
        int getKeyEvent();
        void handleEvents();
        void handleMouseOver();
        void handleMousePress();
        void handleMouseReleased();

        // Getter
        sf::RenderWindow &getWindow() {return _window;}
        GameMenu *getGameMenu() {return _GameMenu;}
        Player *getPlayer() {return _player;}
        enum Scene getScene() {return _scene;}
        OptionMenu *getOptionMenu() {return _OptionMenu;}
        GameMap *getGameMap() {return _gameMap;}
        sf::Music *getMusic() {return &_musicGame;}
        Credit *getCreditMenu() {return _credit;}
        float getVolumeMenu() {return _musicGame.getVolume();}
        GameMap::TimeLine getTimeLine() {return _timeLine;}
        void getTotem();

        //Display
        void DisplayWindow();
        void displayFilter();

        // View
        void setView(sf::View *view) {_view = view;}
        sf::View *getView(void) {return _view;}

        // Setter
        void setScene(enum Scene scene) {_scene = scene;}
        void setGameVolume(float volume) {_musicGame.setVolume(volume);}
        void setTimeLine(GameMap::TimeLine timeLine) {_timeLine = timeLine;}
        void setSpeed(int incr) {getPlayer()->data["speed"] = std::any_cast<int>(getPlayer()->data["speed"]) + incr;}
        void setTotem(int totem);

        //Music
        void playMusic();

        // Player Movement
        void movePlayer(enum Direction dir) {
            if (dir == IDLE || std::any_cast<Direction>(_player->data["direction"]) == IDLE)
                _player->data["direction"] = dir;
        }

        class Error : public std::exception {
            public:
                Error (const std::string &msg)
                {
                    _msg = msg;
                }

                const char *what() const noexcept override
                {
                    return _msg.c_str();
                }
            private:
                std::string _msg;
        };
    private:
        sf::RenderWindow _window;
        sf::View *_view;
        sf::Event _event;
        sf::Music _musicGame;
        GameMenu *_GameMenu;
        Player *_player;
        Credit *_credit;
        OptionMenu *_OptionMenu;
        enum Scene _scene;
        GameMap *_gameMap;
        GameMap::TimeLine _timeLine;
        std::vector<std::string> _filters;

        std::unordered_map<sf::Keyboard::Key, std::function<void()>> _keyFunctions = {
            {sf::Keyboard::Escape, [this](){setScene(GAMEMENU);}},
            {sf::Keyboard::U, [this](){setTimeLine(GameMap::TimeLine::PAST);}},
            {sf::Keyboard::I, [this](){setTimeLine(GameMap::TimeLine::PRESENT);}},
            {sf::Keyboard::O, [this](){setTimeLine(GameMap::TimeLine::FUTUR);}},
            {sf::Keyboard::E, [this](){getTotem();}},
            {sf::Keyboard::F, [this](){setTotem(1);}},
            {sf::Keyboard::G, [this](){setTotem(2);}},
            {sf::Keyboard::H, [this](){setTotem(3);}},
        };

        void setupFilters(void);
};
