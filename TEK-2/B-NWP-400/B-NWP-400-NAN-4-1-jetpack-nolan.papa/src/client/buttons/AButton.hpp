/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Button
*/

#ifndef ABUTTON_HPP_
#define ABUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "IButton.hpp"

#include "../Display.hpp"

class AButton : public IButton {
    public:
        AButton(std::string text, sf::Vector2f pos, sf::Vector2f size);
        ~AButton() = default;

        void display(sf::RenderWindow &window) override;
        bool isOver(sf::RenderWindow &window) override;
        virtual void click(Display &display) = 0;

        void setState(State state) override;
        State getState() override;

        void setTransparency(sf::Uint8 alpha);
        sf::Uint8 getTransparency() const;
        sf::Color getShapeColor() const;
        void setShapeColor(const sf::Color& color);

    private:
        sf::Text _text;
        sf::RectangleShape _shape;
        State _state;
        sf::Font _font;
};

#endif /* !ABUTTON_HPP_ */
