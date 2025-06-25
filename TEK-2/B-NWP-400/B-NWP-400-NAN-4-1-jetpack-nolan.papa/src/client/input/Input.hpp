/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

class Display;

class Input {
    public:
        enum State {
            NORMAL,
            SELECTED
        };

        Input(std::string label, std::string initialValue, sf::Vector2f pos, sf::Vector2f size);
        ~Input();

        void display(sf::RenderWindow &window);
        bool isOver(sf::RenderWindow &window);
        void setState(State state);
        State getState();
        void handleInput(sf::Event event);
        std::string getValue() const;
        void playInputNoise();

    protected:
        sf::RectangleShape _shape;
        sf::Text _text;
        sf::Text _label;
        std::string _value;
        State _state;
        sf::Font _font;
        sf::Music _inputNoise;

        // Animation
        bool _isAnimating;
        sf::Clock _animationClock;
        float _animationDuration;
        sf::Color _normalTextColor;
        sf::Color _animTextColor;
        float _textScaleFactor;

    private:
        void updateText();
        void updateAnimation();
        void triggerAnimation();
};

#endif /* !INPUT_HPP_ */
