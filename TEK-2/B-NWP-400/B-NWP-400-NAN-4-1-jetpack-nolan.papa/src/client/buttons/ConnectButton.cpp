/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** ConnectButton
*/

#include <string>
#include <iostream>

#include "ConnectButton.hpp"
#include "../communication/Communication.hpp"

/**
 * @brief Constructor that initializes a connect button.
 *
 * @param text The text displayed on the button.
 * @param pos The position of the button.
 * @param size The size of the button.
 */
ConnectButton::ConnectButton(std::string text, sf::Vector2f pos, sf::Vector2f size)
: AButton(text, pos, size)
{
}

/**
 * @brief Handles the click event. (Currently not implemented)
 *
 * @param display The display window (unused).
 *
 * @todo Implement the connection logic (IP, port, username).
 */
void ConnectButton::click(Display &display)
{
    if (display.getIsConnected()) {
        display.setIsConnected(false);
        display.stopCommunicationThread();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    display.getCommunication().setIp(display.getIp());
    display.getCommunication().setPort(display.getPort());
    display.getCommunication().setUsername(display.getUsername());
    display.startCommunicationThread();

    std::string error = display.getCommunication().getError();

    if (error == "") {
        display.setIsConnected(true);
    } else {
        std::cerr << error << std::endl;
    }
}
