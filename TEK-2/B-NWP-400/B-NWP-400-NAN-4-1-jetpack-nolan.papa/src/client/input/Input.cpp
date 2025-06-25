/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Input
*/

#include <cmath>
#include <string>

#include "Input.hpp"

/**
 * @brief Constructor that initializes an input field.
 *
 * @param label The label displayed above the input field.
 * @param initialValue The initial value of the input.
 * @param pos The position of the input field.
 * @param size The size of the input field.
 */
Input::Input
(std::string label, std::string initialValue, sf::Vector2f pos, sf::Vector2f size) :
    _value(initialValue),
    _state(State::NORMAL),
    _isAnimating(false),
    _animationDuration(0.3f),
    _textScaleFactor(1.0f)
{
    _font.loadFromFile("assets/fonts/jetpack_font.ttf");
    _normalTextColor = sf::Color::Black;
    _animTextColor = sf::Color(0, 100, 255);

    _text.setFont(_font);
    _text.setString(_value);
    _text.setCharacterSize(24);
    _text.setFillColor(_normalTextColor);

    _label.setFont(_font);
    _label.setString(label);
    _label.setCharacterSize(18);
    _label.setFillColor(sf::Color::White);
    _label.setPosition(pos.x, pos.y - size.y / 2 - 10);

    _shape.setSize(size);
    _shape.setPosition(pos);
    _shape.setFillColor(sf::Color::White);
    _shape.setOutlineColor(sf::Color::Black);
    _shape.setOutlineThickness(2);

    _inputNoise.openFromFile("assets/sounds/top7.wav");

    updateText();
}

/**
 * @brief Displays the input field, including animations if active.
 *
 * @param window The render window where the input field is drawn.
 */
void Input::display(sf::RenderWindow &window)
{
    window.draw(_shape);

    if (_isAnimating)
        updateAnimation();
    window.draw(_text);
    window.draw(_label);
}

/**
 * @brief Checks if the mouse is over the input field.
 *
 * @param window The render window where the input field is displayed.
 *
 * @return true if the mouse is over the input field, false otherwise.
 */
bool Input::isOver(sf::RenderWindow &window)
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
 * @brief Sets the state of the input field.
 *
 * @param state The new state (NORMAL or SELECTED).
 */
void Input::setState(State state)
{
    _state = state;

    switch (state) {
        case State::NORMAL:
            _shape.setOutlineColor(sf::Color::Black);
            break;
        case State::SELECTED:
            _shape.setOutlineColor(sf::Color::Blue);
            break;
    }
}

/**
 * @brief Gets the current state of the input field.
 *
 * @return The current state of the input field.
 */
Input::State Input::getState()
{
    return _state;
}

/**
 * @brief Handles user input events for the input field.
 *
 * @param event The event to process (text input, key press).
 */
void Input::handleInput(sf::Event event)
{
    if (_state != State::SELECTED)
        return;

    if (event.type == sf::Event::TextEntered) {
        bool textChanged = false;

        if (event.text.unicode == 8) {
            if (!_value.empty()) {
                _value.pop_back();
                textChanged = true;
            }
        } else if (event.text.unicode == 13)
            setState(State::NORMAL);
        else if (event.text.unicode < 128) {
            _value += static_cast<char>(event.text.unicode);
            textChanged = true;
        }

        if (textChanged) {
            updateText();
            triggerAnimation();
            playInputNoise();
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter)
            setState(State::NORMAL);
    }
}

/**
 * @brief Gets the current value entered in the input field.
 *
 * @return The current value as a string.
 */
std::string Input::getValue() const
{
    return _value;
}

/**
 * @brief Updates the displayed text to fit within the input field.
 */
void Input::updateText()
{
    _text.setString(_value);
    _text.setScale(1.0f, 1.0f);

    sf::Vector2f padding(10, 5);
    _text.setPosition(_shape.getPosition() + padding);

    float maxWidth = _shape.getSize().x - (padding.x * 2);
    float textWidth = _text.getGlobalBounds().width;
    if (textWidth > maxWidth) {
        float scaleFactor = maxWidth / textWidth;
        _text.setScale(scaleFactor, 1.0f);

        float textHeight = _text.getGlobalBounds().height;
        float verticalCenter = _shape.getPosition().y +
            (_shape.getSize().y / 2) - (textHeight / 2);
        _text.setPosition(_shape.getPosition().x + padding.x, verticalCenter);
    }
}

/**
 * @brief Triggers the input animation effect.
 */
void Input::triggerAnimation()
{
    _isAnimating = true;
    _animationClock.restart();
}

/**
 * @brief Updates the input animation effect.
 */
void Input::updateAnimation()
{
    float elapsed = _animationClock.getElapsedTime().asSeconds();

    if (elapsed > _animationDuration) {
        _isAnimating = false;
        _text.setFillColor(_normalTextColor);
        _text.setScale(_text.getScale().x, 1.0f);
        return;
    }

    float progress = elapsed / _animationDuration;
    float curve = sin(progress * 3.14159f) * (1.0f - progress);

    sf::Color currentColor;
    currentColor.r = _normalTextColor.r + (_animTextColor.r - _normalTextColor.r) * curve;
    currentColor.g = _normalTextColor.g + (_animTextColor.g - _normalTextColor.g) * curve;
    currentColor.b = _normalTextColor.b + (_animTextColor.b - _normalTextColor.b) * curve;

    float scale = 1.0f + (0.2f * curve);
    _text.setScale(_text.getScale().x, scale);
    _text.setFillColor(currentColor);
}

/**
 * @brief Plays the input sound effect when a key is pressed.
 */
void Input::playInputNoise()
{
    _inputNoise.stop();
    _inputNoise.play();
}

/**
 * @brief Destructor for the Input class.
 */
Input::~Input()
{
    _inputNoise.stop();
}
