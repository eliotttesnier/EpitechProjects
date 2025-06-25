/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** PlayButton
*/

#ifndef PLAYBUTTON_HPP_
#define PLAYBUTTON_HPP_

#include "AButton.hpp"

class PlayButton : public AButton {
    public:
        PlayButton(std::string text, sf::Vector2f pos, sf::Vector2f size);
        ~PlayButton() = default;

        void click(Display &display) override;
        void display(sf::RenderWindow &window, Display &display);
        bool isEnabled(Display &display);
};

#endif /* !PLAYBUTTON_HPP_ */
