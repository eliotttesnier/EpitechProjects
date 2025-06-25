/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** PlayButton
*/

#include <string>

#include "PlayButton.hpp"
#include "Display.hpp"

/**
 * @brief Constructor that initializes a play button.
 *
 * @param text The text displayed on the button.
 * @param pos The position of the button.
 * @param size The size of the button.
 */
PlayButton::PlayButton(std::string text, sf::Vector2f pos, sf::Vector2f size)
: AButton(text, pos, size)
{
}

/**
 * @brief Handles the click event by switching to the game scene if enabled.
 *
 * @param display The display window managing the scenes.
 */
void PlayButton::click(Display &display)
{
    if (isEnabled(display))
        display.getCommunication().setShouldSendStartGame(true);
}

/**
 * @brief Displays the play button with appropriate transparency based on its state.
 *
 * @param window The render window where the button should be drawn.
 * @param display The display to check if the button should be enabled.
 */
void PlayButton::display(sf::RenderWindow &window, Display &display)
{
    IButton::State currentState = getState();
    sf::Color currentColor = getShapeColor();

    if (!isEnabled(display))
        setTransparency(128);
    else
        setTransparency(255);

    AButton::display(window);

    if (getTransparency() != 255) {
        setShapeColor(currentColor);
        setState(currentState);
    }
}

/**
 * @brief Checks whether the play button is enabled.
 *
 * @param display The display to check the number of connections.
 *
 * @return true if at least two connections are established, false otherwise.
 */
bool PlayButton::isEnabled(Display &display)
{
    return display.getNbConnections() >= 2;
}
