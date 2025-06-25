/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Menu
*/

#include <string>
#include <memory>

#include "Menu.hpp"
#include "buttons/CloseButton.hpp"
#include "buttons/PlayButton.hpp"
#include "buttons/ConnectButton.hpp"
#include "input/Input.hpp"
#include "Display.hpp"

/**
 * @brief Constructs the Menu with user connection details and initializes UI elements.
 *
 * @param username Reference to the username string.
 * @param ip Reference to the server IP address string.
 * @param port Reference to the server port string.
 */
Menu::Menu(std::string& username, std::string& ip, std::string& port)
    : _username(username), _ip(ip), _port(port)
{
    _jetpackFont.loadFromFile("assets/fonts/jetpack_font.ttf");
    this->initTitle();
    this->initConnectionStatus();
    this->initNbConnections();
    _buttons.push_back(
        std::make_unique<CloseButton>(
            "Close", sf::Vector2f(500, 750), sf::Vector2f(100, 50)
        )
    );
    _buttons.push_back(
        std::make_unique<PlayButton>(
            "Play", sf::Vector2f(200, 750), sf::Vector2f(100, 50)
        )
    );
    _buttons.push_back(
        std::make_unique<ConnectButton>(
            "Connect", sf::Vector2f(350, 750), sf::Vector2f(100, 50)
        )
    );

    _inputs.push_back(
        std::make_unique<Input>(
            "Username", _username, sf::Vector2f(300, 400), sf::Vector2f(200, 40)
        )
    );
    _inputs.push_back(
        std::make_unique<Input>(
            "IP Address", _ip, sf::Vector2f(300, 500), sf::Vector2f(200, 40)
        )
    );
    _inputs.push_back(
        std::make_unique<Input>(
            "Port", _port, sf::Vector2f(300, 600), sf::Vector2f(200, 40)
        )
    );
}

/**
 * @brief Displays the menu, including buttons, inputs, and connection status.
 *
 * @param window The SFML window to render onto.
 * @param display The main Display object managing events and rendering.
 */
void Menu::display(sf::RenderWindow &window, Display &display)
{
    window.draw(_title);
    window.draw(_connectionStatus);
    window.draw(_nbConnectionsText);

    for (auto &button : _buttons) {
        if (auto playBtn = dynamic_cast<PlayButton*>(button.get()))
            playBtn->display(window, display);
        else
            button->display(window);
    }

    for (auto &input : _inputs) {
        input->display(window);
    }

    updateConnectionStatus(display);
    updateNbConnections(display);
}

/**
 * @brief Handles events for buttons and input fields.
 *
 * @param display The main Display object to retrieve events and manage interactions.
 */
void Menu::handleEvents(Display &display)
{
    // button events
    for (auto &button : _buttons) {
        bool isPlayButtonDisabled = false;

        if (auto playBtn = dynamic_cast<PlayButton*>(button.get())) {
            if (!playBtn->isEnabled(display)) {
                isPlayButtonDisabled = true;
                playBtn->setState(IButton::State::NORMAL);
            }
        }

        if (!isPlayButtonDisabled && button->isOver(display.getWindow())) {
            if (display.getEvent().type == sf::Event::MouseButtonPressed)
                button->setState(IButton::State::PRESSED);
            else if (display.getEvent().type == sf::Event::MouseButtonReleased)
                button->click(display);
            else
                button->setState(button->getState() == IButton::State::PRESSED ?
                    IButton::State::PRESSED : IButton::State::HOVER);
        } else
            button->setState(IButton::State::NORMAL);
    }

    // input box events
    if (display.getEvent().type == sf::Event::MouseButtonPressed) {
        for (auto &input : _inputs) {
            if (input->isOver(display.getWindow())) {
                input->setState(Input::State::SELECTED);
            } else {
                input->setState(Input::State::NORMAL);
            }
        }
    }

    // text input
    for (auto &input : _inputs) {
        if (input->getState() == Input::State::SELECTED) {
            input->handleInput(display.getEvent());
        }
    }
    updateVariables();
}

/**
 * @brief Initializes the title text for the menu.
 */
void Menu::initTitle()
{
    _title.setFont(_jetpackFont);
    _title.setString("Djoufara Joyride");
    _title.setCharacterSize(50);
    _title.setFillColor(sf::Color::White);

    sf::FloatRect textRect = _title.getGlobalBounds();
    _title.setPosition(400 - textRect.width / 2, 50 - textRect.height / 2);
}

/**
 * @brief Updates the username, IP address, and port based on input field values.
 */
void Menu::updateVariables()
{
    if (_inputs.size() >= 3) {
        _username = _inputs[0]->getValue();
        _ip = _inputs[1]->getValue();
        _port = _inputs[2]->getValue();
    }
}

/**
 * @brief Initializes the connection status text.
 */
void Menu::initConnectionStatus()
{
    _connectionStatus.setFont(_jetpackFont);
    _connectionStatus.setString("Not connected to server");
    _connectionStatus.setStyle(sf::Text::Bold);
    _connectionStatus.setCharacterSize(20);
    _connectionStatus.setFillColor(sf::Color::White);

    sf::FloatRect textRect = _connectionStatus.getGlobalBounds();
    _connectionStatus.setPosition(400 - textRect.width / 2, 200 - textRect.height / 2);
}

/**
 * @brief Updates the connection status text based on the display's connection state.
 *
 * @param display The Display object used to check connection status.
 */
void Menu::updateConnectionStatus(Display &display)
{
    if (display.getIsConnected())
        _connectionStatus.setString("Connected to server");
    else
        _connectionStatus.setString("Not connected to server");

    sf::FloatRect textRect = _connectionStatus.getGlobalBounds();
    _connectionStatus.setPosition(400 - textRect.width / 2, 200 - textRect.height / 2);
}

/**
 * @brief Initializes the number of connected players text.
 */
void Menu::initNbConnections()
{
    _nbConnectionsText.setFont(_jetpackFont);
    _nbConnectionsText.setString("0 players connected");
    _nbConnectionsText.setStyle(sf::Text::Bold);
    _nbConnectionsText.setCharacterSize(20);
    _nbConnectionsText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = _nbConnectionsText.getGlobalBounds();
    _nbConnectionsText.setPosition(400 - textRect.width / 2, 250 - textRect.height / 2);
}

/**
 * @brief Updates the number of connected players text based on the display state.
 *
 * @param display The Display object used to retrieve the number of connected players.
 */
void Menu::updateNbConnections(Display &display)
{
    _nbConnectionsText.setString(
        std::to_string(display.getNbConnections()) + " players connected"
    );

    sf::FloatRect textRect = _nbConnectionsText.getGlobalBounds();
    _nbConnectionsText.setPosition(400 - textRect.width / 2, 250 - textRect.height / 2);
}
