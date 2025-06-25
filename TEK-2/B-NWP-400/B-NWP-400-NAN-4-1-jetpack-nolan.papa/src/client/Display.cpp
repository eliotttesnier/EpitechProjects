/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Display
*/

#include <iostream>
#include <string>
#include <memory>

#include "Display.hpp"
#include "Menu.hpp"
#include "DisplayGame.hpp"

/**
 * @brief Constructs the Display object and initializes the window, scenes, and assets.
 *
 * @param ip The server IP address.
 * @param port The server port.
 */
Display::Display(std::string ip, std::string port, bool debug)
{
    _ip = ip;
    _port = port;
    _username = "";
    _window.create(sf::VideoMode(800, 900), "Djoufara Joyride");
    _window.setFramerateLimit(60);
    _currentScene = Scene::MENU;

    sf::Texture loadingTexture;
    if (!loadingTexture.loadFromFile("assets/loading_screen.jpg")) {
        std::cerr << "Failed to load loading screen texture" << std::endl;
    } else {
        sf::Sprite loadingSprite;
        loadingSprite.setTexture(loadingTexture);
        loadingSprite.setScale(
            static_cast<float>(_window.getSize().x) / loadingTexture.getSize().x,
            static_cast<float>(_window.getSize().y) / loadingTexture.getSize().y
        );

        _window.clear();
        _window.draw(loadingSprite);
        _window.display();
    }

    _menu = std::make_unique<Menu>(_username, _ip, _port);
    _gamescene = std::make_unique<GameScene>(_username);

    _cursorTexture.loadFromFile("assets/cursor.png");
    _cursor.setTexture(_cursorTexture);
    _cursor.setScale(0.25f, 0.25f);
    _cursor.setOrigin(sf::Vector2f(40, 240));
    _window.setMouseCursorVisible(false);

    _clickNoise.openFromFile("assets/sounds/fave_calm.wav");

    _isConnected = false;
    _nbConnections = 0;
    _communication.setDebugMode(debug);
}

/**
 * @brief Destructor that ensures the window is closed.
 */
Display::~Display()
{
    if (_window.isOpen())
        _window.close();
    _communication.setNeedsToClose(true);
    if (_communicationThread.joinable())
        _communicationThread.join();
    _clickNoise.stop();
}

/**
 * @brief Main loop that handles events, clears the screen, and displays the current scene.
 */
void Display::run()
{
    while (_window.isOpen()) {
        std::string error = _communication.getError();
        if (error != "") {
            std::cerr << error << std::endl;
        }

        if (_communication.getGameStart() == true &&
            _currentScene == Scene::MENU) {
            setCurrentScene(Display::Scene::GAME);
        }

        if (_currentScene == Scene::MENU) {
            _nbConnections = _communication.getNbPlayers();
        }

        _gamescene->setUsername(_username);
        if (_currentScene == Scene::GAME) {
            _gamescene->setPlayers(_communication.getPlayers());
            _gamescene->setCoins(_communication.getCoins());
            _gamescene->setObstacles(_communication.getObstacles());
            if (_gamescene->getGameEnd() == false) {
                if (_communication.getGameEnd() == true)
                    _gamescene->setGameEnd(true);
            }
        }

        handleEvents();
        clear();
        display();
    }
}

/**
 * @brief Closes the application window.
 */
void Display::close()
{
    _window.close();
}

/**
 * @brief Handles user input events such as closing the window and clicking.
 */
void Display::handleEvents()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();

        if (_event.type == sf::Event::MouseButtonPressed) {
            _clickNoise.stop();
            std::srand(static_cast<unsigned int>(time(nullptr)));
            float randomPitch = 0.35f + static_cast<float>(
                std::rand()) / (static_cast<float>(RAND_MAX / (2.5f - 0.35f))
            );
            _clickNoise.setPitch(randomPitch);
            _clickNoise.play();
        }

        if (_currentScene == Scene::MENU)
            _menu->handleEvents(*this);
        if (_currentScene == Scene::GAME)
            _gamescene->handleEvents(*this);
    }
    _communication.setIp(_ip);
    _communication.setPort(_port);
    _communication.setUsername(_username);
}

/**
 * @brief Clears the window before rendering a new frame.
 */
void Display::clear()
{
    _window.clear();
}

/**
 * @brief Displays the current scene and updates the cursor position.
 */
void Display::display()
{
    if (_currentScene == Scene::MENU)
        _menu->display(_window, *this);
    if (_currentScene == Scene::GAME) {
        _gamescene->display(_window);
    }

    _cursor.setPosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);
    _window.draw(_cursor);

    _window.display();
}

/**
 * @brief Gets the latest event captured from the event queue.
 *
 * @return The most recent SFML event.
 */
sf::Event Display::getEvent()
{
    return _event;
}

/**
 * @brief Provides access to the main render window.
 *
 * @return Reference to the SFML render window.
 */
sf::RenderWindow &Display::getWindow()
{
    return _window;
}

/**
 * @brief Gets the currently active scene.
 *
 * @return The current scene (MENU or GAME).
 */
Display::Scene Display::getCurrentScene()
{
    return _currentScene;
}

/**
 * @brief Sets the current scene and adjusts the window size accordingly.
 *
 * @param scene The new scene to set.
 */
void Display::setCurrentScene(Scene scene)
{
    if (_currentScene == Scene::GAME && scene == Scene::MENU) {
        _gamescene->stopSounds();
    }
    _currentScene = scene;
    if (scene == Scene::GAME)
        _window.setSize(sf::Vector2u(1920, 1080));
    else
        _window.setSize(sf::Vector2u(800, 900));
    _window.setView(sf::View(sf::FloatRect(0, 0, _window.getSize().x, _window.getSize().y)));
}

/**
 * @brief Gets the username of the current player.
 *
 * @return The player's username as a string.
 */
std::string Display::getUsername() const
{
    return _username;
}

/**
 * @brief Gets the server IP address.
 *
 * @return The server IP as a string.
 */
std::string Display::getIp() const
{
    return _ip;
}

/**
 * @brief Gets the server port.
 *
 * @return The server port as a string.
 */
std::string Display::getPort() const
{
    return _port;
}

/**
 * @brief Checks if the player is currently connected to the server.
 *
 * @return true if connected, false otherwise.
 */
bool Display::getIsConnected() const
{
    return _isConnected;
}

/**
 * @brief Sets the connection status of the player.
 *
 * @param isConnected The new connection status.
 */
void Display::setIsConnected(bool isConnected)
{
    _isConnected = isConnected;
}

/**
 * @brief Gets the number of active connections to the server.
 *
 * @return The number of connections.
 */
std::size_t Display::getNbConnections() const
{
    return _nbConnections;
}

/**
 * @brief Sets the number of active connections to the server.
 *
 * @param nbConnections The new number of connections.
 */
void Display::setNbConnections(std::size_t nbConnections)
{
    _nbConnections = nbConnections;
}

/**
 * @brief Gets the communication instance.
 *
 * Returns a reference to the `Communication` instance used by the display.
 *
 * @return A reference to the `Communication` object.
 */
Communication &Display::getCommunication()
{
    return _communication;
}

/**
 * @brief Sets the username for the display.
 *
 * Updates the display's username with the provided string.
 *
 * @param username The new username to set.
 */
void Display::setUsername(std::string username)
{
    _username = username;
}

/**
 * @brief Sets the IP address for the display.
 *
 * Updates the stored IP address to the given value.
 *
 * @param ip The new IP address to set.
 */
void Display::setIp(std::string ip)
{
    _ip = ip;
}

/**
 * @brief Sets the port for the display.
 *
 * Updates the stored port number with the provided value.
 *
 * @param port The new port number to set.
 */
void Display::setPort(std::string port)
{
    _port = port;
}

/**
 * @brief Starts the communication thread.
 *
 * Stops any existing communication thread, resets the communication state,
 * and launches a new thread to handle communication asynchronously.
 */
void Display::startCommunicationThread()
{
    stopCommunicationThread();
    _communication.setNeedsToClose(false);
    _communicationThread = std::thread([this]() { _communication.connectToServer(); });
}

/**
 * @brief Stops the communication thread.
 *
 * Signals the communication system to close and waits for the communication
 * thread to finish execution if it is joinable.
 */
void Display::stopCommunicationThread()
{
    _communication.setNeedsToClose(true);
    if (_communicationThread.joinable())
        _communicationThread.join();
}
