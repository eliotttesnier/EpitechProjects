/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** ConnectButton
*/

#ifndef CONNECTBUTTON_HPP_
#define CONNECTBUTTON_HPP_

#include "AButton.hpp"

class ConnectButton : public AButton {
    public:
        ConnectButton(std::string text, sf::Vector2f pos, sf::Vector2f size);
        ~ConnectButton() = default;

        void click(Display &display) override;
};

#endif /* !CONNECTBUTTON_HPP_ */
