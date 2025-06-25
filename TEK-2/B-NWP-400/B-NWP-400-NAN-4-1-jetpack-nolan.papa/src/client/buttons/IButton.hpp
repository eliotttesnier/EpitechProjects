/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** IButton
*/

#ifndef IBUTTON_HPP_
#define IBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Display;

class IButton {
    public:
        enum State {
            NORMAL,
            HOVER,
            PRESSED
        };

        virtual ~IButton() = default;

        virtual void display(sf::RenderWindow &window) = 0;
        virtual bool isOver(sf::RenderWindow &window) = 0;
        virtual void click(Display &display) = 0;

        virtual void setState(State state) = 0;
        virtual State getState() = 0;
};

#endif /* !IBUTTON_HPP_ */
