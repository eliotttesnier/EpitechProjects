/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** CloseButton
*/

#ifndef CLOSEBUTTON_HPP_
#define CLOSEBUTTON_HPP_

#include "AButton.hpp"

class CloseButton : public AButton{
    public:
        CloseButton(std::string text, sf::Vector2f pos, sf::Vector2f size);
        ~CloseButton() = default;

        void click(Display &display) override;
};

#endif /* !CLOSEBUTTON_HPP_ */
