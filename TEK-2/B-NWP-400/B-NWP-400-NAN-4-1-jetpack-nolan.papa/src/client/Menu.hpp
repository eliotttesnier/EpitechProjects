/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <memory>

#include "buttons/IButton.hpp"
#include "input/Input.hpp"

class Menu {
    public:
        Menu(std::string& username, std::string& ip, std::string& port);
        ~Menu() = default;

        void display(sf::RenderWindow &window, Display &display);
        void handleEvents(Display &display);
        void updateVariables();

    private:
        std::string& _username;
        std::string& _ip;
        std::string& _port;

        sf::Text _title;
        sf::Font _jetpackFont;

        sf::Text _connectionStatus;
        sf::Text _nbConnectionsText;

        std::vector<std::unique_ptr<IButton>> _buttons;
        std::vector<std::unique_ptr<Input>> _inputs;

        void initTitle();
        void initConnectionStatus();
        void initNbConnections();
        void updateConnectionStatus(Display &display);
        void updateNbConnections(Display &display);
};

#endif /* !MENU_HPP_ */
