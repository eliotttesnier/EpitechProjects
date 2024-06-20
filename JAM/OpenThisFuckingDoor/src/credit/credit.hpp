/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** credit
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <functional>

class Credit {
    public:
        Credit();

        void textCreditGroup();
        void textCreditSource();
        // Display GameMenu
        void displayCredit();

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
        sf::Text _textGroup;
        sf::Text _textSource;
};