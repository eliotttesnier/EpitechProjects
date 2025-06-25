/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Display
*/

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <memory>
#include <thread>

#include "communication/Communication.hpp"

class Menu;
class GameScene;

class Display {
    public:
        enum Scene {
            MENU,
            GAME
        };

        Display(std::string ip, std::string port, bool debug);
        ~Display();

        void run();
        void close();

        sf::Event getEvent();
        sf::RenderWindow &getWindow();
        Scene getCurrentScene();
        Communication &getCommunication();

        void setCurrentScene(Scene scene);
        void setIsConnected(bool isConnected);
        void setNbConnections(std::size_t nbConnections);

        std::string getUsername() const;
        std::string getIp() const;
        std::string getPort() const;

        void setUsername(std::string username);
        void setIp(std::string ip);
        void setPort(std::string port);

        bool getIsConnected() const;
        std::size_t getNbConnections() const;

        void startCommunicationThread();
        void stopCommunicationThread();

    private:
        std::string _ip;
        std::string _port;
        std::string _username;

        std::unique_ptr<Menu> _menu;
        std::unique_ptr<GameScene> _gamescene;
        sf::RenderWindow _window;
        sf::Event _event;
        Scene _currentScene;

        sf::Sprite _cursor;
        sf::Texture _cursorTexture;
        sf::Music _clickNoise;

        Communication _communication;
        bool _isConnected;
        std::size_t _nbConnections;

        std::thread _communicationThread;

        void handleEvents();
        void clear();
        void display();
};

#endif /* !DISPLAY_HPP_ */
