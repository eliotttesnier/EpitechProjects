/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** GameMenu
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <functional>
#include "button.hpp"
#include <iostream>

class GameMenu {
    public:
        GameMenu();

        // title
        void titleGameMenu();
        void textGameMenu();
        // Display GameMenu
        void displayGameMenu();

        // getbutton
        std::vector<Button *> getbutton() {return _buttons;}
        // button
        void addButton(std::string path, std::pair<float, float> pos, std::pair<float, float> size, Button::ButtonType type);
        void setupButton(std::vector<Button *> _buttons);
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
        sf::Font _fontText;
        sf::Text _textJouer;
        sf::Text _textTitle;
        std::vector<Button *> _buttons;
};