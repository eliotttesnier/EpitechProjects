/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Button
*/

#include <string>

#include "AButton.hpp"

/**
 * @brief Constructor that initializes a button with text, position, and size.
 *
 * @param text The text displayed on the button.
 * @param pos The position of the button.
 * @param size The size of the button.
 *
 * @throws If the font file cannot be loaded, `sf::Font::loadFromFile` may throw an exception.
 */
AButton::AButton(std::string text, sf::Vector2f pos, sf::Vector2f size)
{
    _font.loadFromFile("assets/fonts/jetpack_font.ttf");
    _text.setFont(_font);
    _text.setString(text);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);

    _shape.setSize(size);
    _shape.setPosition(pos);
    _shape.setFillColor(sf::Color::Black);
    _shape.setOutlineColor(sf::Color::White);
    _shape.setOutlineThickness(2);

    sf::FloatRect textBounds = _text.getLocalBounds();
    _text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);
    _text.setPosition(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f);

    _state = State::NORMAL;
}

/**
 * @brief Draws the button shape and text onto the provided render window.
 *
 * @param window The render window where the button should be drawn.
 */
void AButton::display(sf::RenderWindow &window)
{
    window.draw(_shape);
    window.draw(_text);
}


/**
 * @brief Checks whether the mouse cursor is hovering over the button.
 *
 * @param window The render window to get the mouse position relative to.
 *
 * @return true if the mouse cursor is over the button, false otherwise.
 */
bool AButton::isOver(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (
        mousePos.x >= _shape.getPosition().x &&
        mousePos.x <= _shape.getPosition().x + _shape.getSize().x &&
        mousePos.y >= _shape.getPosition().y &&
        mousePos.y <= _shape.getPosition().y + _shape.getSize().y
    ) {
        return true;
    }

    return false;
}

/**
 * @brief Changes the button's state and updates its visual appearance.
 *
 * @param state The new state of the button (`NORMAL`, `HOVER`, or `PRESSED`).
 */
void AButton::setState(State state)
{
    _state = state;

    switch (state) {
        case State::NORMAL:
            _shape.setFillColor(sf::Color::Black);
            break;
        case State::HOVER:
            _shape.setFillColor(sf::Color::Blue);
            break;
        case State::PRESSED:
            _shape.setFillColor(sf::Color::Red);
            break;
    }
}

/**
 * @brief Retrieves the current state of the button.
 *
 * @return The current state of the button (`NORMAL`, `HOVER`, or `PRESSED`).
 */
IButton::State AButton::getState()
{
    return _state;
}

/**
 * @brief Sets the transparency (alpha value) of the button's text, shape, and outline.
 *
 * @param alpha The transparency level (0 = fully transparent, 255 = fully opaque).
 */
void AButton::setTransparency(sf::Uint8 alpha)
{
    sf::Color textColor = _text.getFillColor();
    textColor.a = alpha;
    _text.setFillColor(textColor);

    sf::Color shapeColor = _shape.getFillColor();
    shapeColor.a = alpha;
    _shape.setFillColor(shapeColor);

    sf::Color outlineColor = _shape.getOutlineColor();
    outlineColor.a = alpha;
    _shape.setOutlineColor(outlineColor);
}

/**
 * @brief Retrieves the current transparency (alpha value) of the button.
 *
 * @return The alpha value (0-255) of the button's shape color.
 */
sf::Uint8 AButton::getTransparency() const
{
    return _shape.getFillColor().a;
}

/**
 * @brief Gets the current color of the button's shape.
 *
 * @return An `sf::Color` representing the shape's current color.
 */
sf::Color AButton::getShapeColor() const
{
    return _shape.getFillColor();
}

/**
 * @brief Sets the color of the button's shape.
 *
 * @param color The new color to apply to the button's shape.
 */
void AButton::setShapeColor(const sf::Color& color)
{
    _shape.setFillColor(color);
}
