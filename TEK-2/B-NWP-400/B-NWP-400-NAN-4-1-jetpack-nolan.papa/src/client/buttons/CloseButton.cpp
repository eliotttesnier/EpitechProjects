/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** CloseButton
*/

#include <string>

#include "CloseButton.hpp"
#include "Display.hpp"

/**
 * @brief Constructor that initializes a close button.
 *
 * @param text The text displayed on the button.
 * @param pos The position of the button.
 * @param size The size of the button.
 */
CloseButton::CloseButton(std::string text, sf::Vector2f pos, sf::Vector2f size)
: AButton(text, pos, size)
{
}

/**
 * @brief Handles the click event by closing the display window.
 *
 * @param display The display window to be closed.
 */
void CloseButton::click(Display &display)
{
    display.close();
}
