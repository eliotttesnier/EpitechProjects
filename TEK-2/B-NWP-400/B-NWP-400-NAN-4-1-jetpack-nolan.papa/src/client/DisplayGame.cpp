/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** DisplayGame
*/

#include "DisplayGame.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>

#include "entities/CoinEntity.hpp"
#include "entities/ElectricEntity.hpp"


const int MINIMUM_Y_POS = 225;
const int MAXIMUM_Y_POS = 850;
const int CELL_SIZE_X = 134 / 2;
const int CELL_SIZE_Y = (MAXIMUM_Y_POS - MINIMUM_Y_POS) / 10;

/**
 * @brief Constructs the GameScene and initializes textures and background.
 *
 * @param username The username of the player.
 */
GameScene::GameScene(std::string username)
{
    _username = username;
    _gridDebug = false;
    _gameEnded = false;
    _isWinner = false;
    _isJetpackActive = false;
    _prevCoinCount = 0;
    _musicStarted = false;
    _dogLaughPlayed = false;
    _videoDuration = 5.0f;
    _currentFrameIndex = 0;
    loadTextures();
    loadSounds();
    loadDogLaughFrames();
    initBackground();

    _playerSprite.setTexture(_textures["player"]);
    _electricSprite.setTexture(_textures["electric"]);
    _coinSprite.setTexture(_textures["coin"]);

    _coinsTextHUD.setFont(_font);
    _coinsTextHUD.setCharacterSize(20);
    _coinsTextHUD.setOutlineThickness(1);
    _coinsTextHUD.setOutlineColor(sf::Color::Black);

    _usernameTextHUD.setFont(_font);
    _usernameTextHUD.setCharacterSize(22);
    _usernameTextHUD.setOutlineThickness(1);
    _usernameTextHUD.setOutlineColor(sf::Color::Black);
    _usernameTextHUD.setStyle(sf::Text::Bold);

    _usernameText.setFont(_font);
    _usernameText.setCharacterSize(20);
    _usernameText.setFillColor(sf::Color::White);
    _usernameText.setStyle(sf::Text::Bold);
    _usernameText.setOutlineColor(sf::Color::Black);
    _usernameText.setOutlineThickness(2);

    if (!_font.loadFromFile("assets/fonts/jetpack_font.ttf"))
        std::cerr << "Error: cannot open font" << std::endl;
}

/**
 * @brief Destructor for the GameScene.
 */
GameScene::~GameScene()
{
    stopSounds();
}

/**
 * @brief Loads all sound effects and music for the game.
 */
void GameScene::loadSounds()
{
    if (!_themeMusic.openFromFile("assets/sounds/theme.ogg")) {
        std::cerr << "Error: cannot open theme.ogg" << std::endl;
    }
    _themeMusic.setLoop(true);
    _themeMusic.setVolume(20);

    if (!_coinPickupBuffer.loadFromFile("assets/sounds/coin_pickup_1.wav")) {
        std::cerr << "Error: cannot open coin_pickup_1.wav" << std::endl;
    }
    _coinPickupSound.setBuffer(_coinPickupBuffer);
    _coinPickupSound.setVolume(100);

    if (!_zapperDeathBuffer.loadFromFile("assets/sounds/dud_zapper_pop.wav")) {
        std::cerr << "Error: cannot open dud_zapper_pop.wav" << std::endl;
    }
    _zapperDeathSound.setBuffer(_zapperDeathBuffer);

    if (!_jetpackStartBuffer.loadFromFile("assets/sounds/jetpack_start.wav")) {
        std::cerr << "Error: cannot open jetpack_start.wav" << std::endl;
    }
    _jetpackStartSound.setBuffer(_jetpackStartBuffer);
    _jetpackStartSound.setVolume(100);

    if (!_jetpackLoopBuffer.loadFromFile("assets/sounds/jetpack_lp.wav")) {
        std::cerr << "Error: cannot open jetpack_lp.wav" << std::endl;
    }
    _jetpackLoopSound.setBuffer(_jetpackLoopBuffer);
    _jetpackLoopSound.setLoop(true);
    _jetpackLoopSound.setVolume(100);

    if (!_jetpackStopBuffer.loadFromFile("assets/sounds/jetpack_stop.wav")) {
        std::cerr << "Error: cannot open jetpack_stop.wav" << std::endl;
    }
    _jetpackStopSound.setBuffer(_jetpackStopBuffer);
    _jetpackStopSound.setVolume(100);

    if (!_dogLaughBuffer.loadFromFile("assets/video/dog_laugh.wav")) {
        std::cerr << "Error: cannot open dog_laugh.wav" << std::endl;
    }
    _dogLaughSound.setBuffer(_dogLaughBuffer);
    _dogLaughSound.setVolume(100);
}

/**
 * @brief Updates sound effects based on game state changes.
 */
void GameScene::updateSounds()
{
    player_t* currentSelf = nullptr;
    static bool wasDead = false;

    for (auto& player : _players) {
        if (player.username == _username) {
            currentSelf = &player;
            break;
        }
    }
    if (!currentSelf)
        return;

    if (currentSelf->is_jetpack_on) {
        if (!_isJetpackActive) {
            _jetpackStartSound.play();
        }
        if (_isJetpackActive && _jetpackStartSound.getStatus() != sf::Sound::Playing &&
            _jetpackLoopSound.getStatus() != sf::Sound::Playing) {
            _jetpackLoopSound.play();
            _jetpackStartSound.stop();
        }
        _isJetpackActive = true;
    } else {
        if (_isJetpackActive)
            _jetpackStopSound.play();
        _jetpackLoopSound.stop();
        _isJetpackActive = false;
    }

    if (currentSelf->coins_collected > _prevCoinCount) {
        _coinPickupSound.play();
        _prevCoinCount = currentSelf->coins_collected;
    }

    if (!wasDead && currentSelf->is_dead)
        _zapperDeathSound.play();
    wasDead = currentSelf->is_dead;
}

/**
 * @brief Loads textures for the player, coins, and electric obstacles.
 *        Displays an error message if a texture cannot be loaded.
 */
void GameScene::loadTextures()
{
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/player_sprite_sheet.png")) {
        std::cerr << "Error: cannot open player_sprite_sheet.png" << std::endl;
    }
    _textures["player"] = playerTexture;

    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("assets/coins_sprite_sheet.png")) {
        std::cerr << "Error: cannot open coins_sprite_sheet.png" << std::endl;
    }
    _textures["coin"] = coinTexture;

    sf::Texture electricTexture;
    if (!electricTexture.loadFromFile("assets/zapper_sprite_sheet.png")) {
        std::cerr << "Error: cannot open zapper_sprite_sheet.png" << std::endl;
    }
    _textures["electric"] = electricTexture;

    sf::Texture winTexture;
    if (!winTexture.loadFromFile("assets/win.png")) {
        std::cerr << "Error: cannot open win.png" << std::endl;
    }
    _textures["win"] = winTexture;
    _winSprite.setTexture(_textures["win"]);
    _winSprite.setOrigin(
        _winSprite.getGlobalBounds().width / 2,
        _winSprite.getGlobalBounds().height / 2
    );
    _winSprite.setPosition(1920 / 2, 1080 / 2 - 100);

    sf::Texture loseTexture;
    if (!loseTexture.loadFromFile("assets/lose.png")) {
        std::cerr << "Error: cannot open lose.png" << std::endl;
    }
    _textures["lose"] = loseTexture;
    _loseSprite.setTexture(_textures["lose"]);
    _loseSprite.setOrigin(
        _loseSprite.getGlobalBounds().width / 2,
        _loseSprite.getGlobalBounds().height / 2
    );
    _loseSprite.setPosition(1920 / 2, 1080 / 2 - 100);

    if (!_backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "Error: cannot open background" << std::endl;
    }
}

/**
 * @brief Loads all frames from the dog_laugh video folder.
 */
void GameScene::loadDogLaughFrames()
{
    std::string videoFolderPath = "assets/video/dog_laugh";

    try {
        if (!std::filesystem::exists(videoFolderPath)) {
            std::cerr << "Error: Video folder does not exist: " <<
                videoFolderPath << std::endl;
            return;
        }

        std::vector<std::string> frameFiles;
        for (const auto& entry : std::filesystem::directory_iterator(videoFolderPath)) {
            if (entry.path().extension() == ".png") {
                frameFiles.push_back(entry.path().string());
            }
        }

        std::sort(
            frameFiles.begin(),
            frameFiles.end(),
            [](const std::string& a, const std::string& b) {
                std::string fileNameA = a.substr(a.find_last_of('/') + 1);
                std::string fileNameB = b.substr(b.find_last_of('/') + 1);
                int numA = std::stoi(fileNameA.substr(0, fileNameA.find_last_of('.')));
                int numB = std::stoi(fileNameB.substr(0, fileNameB.find_last_of('.')));
                return numA < numB;
            }
        );

        for (const auto& filePath : frameFiles) {
            sf::Texture frameTexture;
            if (frameTexture.loadFromFile(filePath)) {
                _dogLaughFrames.push_back(frameTexture);
            } else {
                std::cerr << "Error: Failed to load texture from " << filePath << std::endl;
            }
        }

        if (!_dogLaughFrames.empty()) {
            _videoDuration = _dogLaughFrames.size() / 10.0f;
            _videoSprite.setTexture(_dogLaughFrames[0]);
            _videoSprite.setScale(0.5f, 0.5f);
            _videoSprite.setOrigin(
                _videoSprite.getGlobalBounds().width / 2,
                _videoSprite.getGlobalBounds().height / 2
            );
            _videoSprite.setPosition(1920 / 1.5, 1080 / 2);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading video frames: " << e.what() << std::endl;
    }
}

/**
 * @brief Initializes the background sprites and their positions for smooth scrolling.
 */
void GameScene::initBackground()
{
    _backgroundSprite_first.setTexture(_backgroundTexture);
    _backgroundSprite_second.setTexture(_backgroundTexture);
    _backgroundSprite_first.setScale(3.16f, 3.16f);
    _backgroundSprite_second.setScale(3.16f, 3.16f);
    _backgroundSprite_second.setPosition(_backgroundSprite_first.getGlobalBounds().width, 0);
}

/**
 * @brief Handles events for the game scene.
 *
 * @param display Reference to the main Display object.
 */
void GameScene::handleEvents(Display& display)
{
    static bool isSpacePressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isSpacePressed) {
        isSpacePressed = true;
        display.getCommunication().setUserFlying(true);
        display.getCommunication().setPacketToSend(true);
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isSpacePressed) {
        isSpacePressed = false;
        display.getCommunication().setUserFlying(false);
        display.getCommunication().setPacketToSend(true);
    }

    if (display.getEvent().type == sf::Event::KeyReleased) {
        if (display.getEvent().key.code == sf::Keyboard::G)
            _gridDebug = !_gridDebug;
    }
}

/**
 * @brief Updates the background scrolling animation.
 */
void GameScene::update()
{
    static sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();

    float scrollSpeed = 300.0f;

    _backgroundSprite_first.move(-scrollSpeed * deltaTime, 0);
    _backgroundSprite_second.move(-scrollSpeed * deltaTime, 0);

    if (
        _backgroundSprite_first.getPosition().x +
        _backgroundSprite_first.getGlobalBounds().width <= 0)
    {
        _backgroundSprite_first.setPosition(_backgroundSprite_second.getPosition().x +
            _backgroundSprite_second.getGlobalBounds().width, 0);
    }

    if (
        _backgroundSprite_second.getPosition().x +
        _backgroundSprite_second.getGlobalBounds().width <= 0)
    {
        _backgroundSprite_second.setPosition(_backgroundSprite_first.getPosition().x +
            _backgroundSprite_first.getGlobalBounds().width, 0);
    }
}

/**
 * @brief Renders the game scene, including the scrolling background.
 *
 * @param window The SFML window to render onto.
 */
void GameScene::display(sf::RenderWindow& window)
{
    if (!_musicStarted) {
        _themeMusic.play();
        _musicStarted = true;
    }

    update();
    updateSounds();

    window.draw(_backgroundSprite_first);
    window.draw(_backgroundSprite_second);

    displayCoins(window);
    displayElectrics(window);
    displayPlayers(window);
    displayHUD(window);

    if (_gridDebug)
        displayDebug(window);

    if (_gameEnded) {
        checkWinners();
        displayGameEndScreen(window);
    }
}

/**
 * @brief Displays the a debug information overlay.
 *
 * @param window The SFML window to render onto.
 */
void GameScene::displayDebug(sf::RenderWindow& window)
{
    static sf::RectangleShape grid;
    float beginX = (_obstacles.empty()) ?
        0 : (
            _obstacles[0].x_pos > 0 ?
                _obstacles[0].x_pos : _obstacles[0].x_pos
            );
    beginX = 200 + (beginX * CELL_SIZE_X);
    if (beginX > 0)
        beginX -= (CELL_SIZE_X * 50);

    grid.setFillColor(sf::Color(0, 0, 0, 0));
    grid.setOutlineColor(sf::Color(255, 0, 0, 50));
    grid.setOutlineThickness(1);
    grid.setSize(sf::Vector2f(CELL_SIZE_X, CELL_SIZE_Y));

    for (int i = 0; i < 10; i++) {
        float realYPos = MINIMUM_Y_POS + (i / 10.0) * (MAXIMUM_Y_POS - MINIMUM_Y_POS);
        for (float x = beginX; x < 1920; x += CELL_SIZE_X) {
            grid.setPosition(x, realYPos);
            window.draw(grid);
        }
    }
}

/**
 * @brief Stops all sounds, particularly when transitioning to menu.
 */
void GameScene::stopSounds()
{
    _themeMusic.stop();
    _jetpackLoopSound.stop();
    _jetpackStartSound.stop();
    _jetpackStopSound.stop();
    _dogLaughSound.stop();
    _musicStarted = false;
    _dogLaughPlayed = false;
}

/**
 * @brief Displays the HUD (Heads-Up Display) with player information.
 *
 * @param window The SFML window to render onto.
 */
void GameScene::displayHUD(sf::RenderWindow& window)
{
    player_t selfPlayer;
    bool foundSelf = false;

    for (const auto& player : _players) {
        if (strcmp(player.username, this->_username.c_str()) == 0) {
            selfPlayer = player;
            foundSelf = true;
            break;
        }
    }

    if (foundSelf) {
        _usernameTextHUD.setString(
            (strcmp(selfPlayer.username, "") == 0) ? "No Name" : selfPlayer.username
        );
        _usernameTextHUD.setFillColor(sf::Color::Yellow);
        _usernameTextHUD.setPosition(10, 10);
        window.draw(_usernameTextHUD);

        _coinsTextHUD.setString("Coins: " + std::to_string(selfPlayer.coins_collected));
        _coinsTextHUD.setFillColor(sf::Color::Yellow);
        _coinsTextHUD.setPosition(10, 40);
        window.draw(_coinsTextHUD);
    }

    int xOffset = 200;
    const int playerInfoWidth = 120;

    for (const auto& player : _players) {
        if (strcmp(player.username, this->_username.c_str()) == 0)
            continue;

        _usernameTextHUD.setString(
            (strcmp(player.username, "") == 0) ? "No Name" : player.username
        );
        _usernameTextHUD.setFillColor(sf::Color::White);
        _usernameTextHUD.setPosition(xOffset, 10);
        window.draw(_usernameTextHUD);

        _coinsTextHUD.setString("Coins: " + std::to_string(player.coins_collected));
        _coinsTextHUD.setFillColor(sf::Color::White);
        _coinsTextHUD.setPosition(xOffset, 35);
        window.draw(_coinsTextHUD);

        xOffset += playerInfoWidth;
    }
}

/**
 * @brief Displays the win or lose screen based on game outcome.
 *
 * @param window The SFML window to render onto.
 */
void GameScene::displayGameEndScreen(sf::RenderWindow& window)
{
    static sf::RectangleShape overlay;

    overlay.setSize(sf::Vector2f(1920, 1080));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    _jetpackLoopSound.stop();
    _jetpackStartSound.stop();
    _jetpackStopSound.stop();
    if (_isWinner) {
        window.draw(_winSprite);
        return;
    }
    if (!_dogLaughPlayed && _isWinner == false) {
        _themeMusic.setVolume(10);
        _dogLaughSound.play();
        _dogLaughPlayed = true;
    }

    window.draw(_loseSprite);
    if (_dogLaughFrames.empty())
        return;

    auto currentTime = std::chrono::steady_clock::now();
    float elapsedSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        currentTime - _gameEndTime).count() / 1000.0f;
    float loopedTime = std::fmod(elapsedSeconds, _videoDuration);

    const int framesPerSecond = 10;
    int frameIndex = static_cast<int>(loopedTime * framesPerSecond);
    frameIndex = std::min(frameIndex, static_cast<int>(_dogLaughFrames.size() - 1));

    if (frameIndex != _currentFrameIndex) {
        _currentFrameIndex = frameIndex;
        _videoSprite.setTexture(_dogLaughFrames[_currentFrameIndex]);
        _videoSprite.setOrigin(
            _videoSprite.getGlobalBounds().width / 2,
            _videoSprite.getGlobalBounds().height / 2
        );
    }
    window.draw(_videoSprite);
}

/**
 * @brief Checks if any player has won based on coin counts.
 * If players have the same number of coins and no player has more, all are winners.
 *
 * @param anyPlayerDead Boolean indicating if any player is dead
 */
void GameScene::checkWinners()
{
    std::vector<player_t*> alivePlayers;
    player_t* selfPlayer = nullptr;
    bool someoneDead = false;

    for (auto& player : _players) {
        if (player.username == _username) {
            selfPlayer = &player;
        }

        if (!player.is_dead) {
            alivePlayers.push_back(&player);
        } else {
            someoneDead = true;
        }
    }

    if (!selfPlayer)
        return;

    if (selfPlayer->is_dead) {
        _isWinner = false;
        return;
    } else if (someoneDead) {
        _isWinner = true;
        return;
    }

    int maxCoins = 0;
    for (const auto& player : alivePlayers) {
        if (player->coins_collected > maxCoins) {
            maxCoins = player->coins_collected;
        }
    }

    bool multiplePlayers = false;
    for (const auto& player : alivePlayers) {
        if (player->coins_collected == maxCoins) {
            if (player->username == _username) {
                _isWinner = true;
            } else if (selfPlayer->coins_collected < maxCoins) {
                _isWinner = false;
                multiplePlayers = true;
            }
        }
    }

    if (!multiplePlayers && selfPlayer->coins_collected == maxCoins) {
        _isWinner = true;
    }
}

/**
 * @brief Displays a single electric obstacle in the game scene.
 *
 * @param window The SFML window to render onto.
 * @param electric The obstacle_t object representing the electric obstacle.
 * @param frameWidth The width of the animation frame.
 */
void GameScene::displayElectric(sf::RenderWindow& window, obstacle_t electric, int frameWidth)
{
    int realYPos = MINIMUM_Y_POS + (electric.y_pos / 10.0) * (MAXIMUM_Y_POS - MINIMUM_Y_POS);
    int realXpos = 200 + (electric.x_pos * CELL_SIZE_X);

    int frameHeight = 122;
    int frameWidth_actual = 105;
    _electricSprite.setTextureRect(sf::IntRect(frameWidth, 0, frameWidth_actual, frameHeight));

    float scaleX = static_cast<float>(CELL_SIZE_X) / frameWidth_actual;
    float scaleY = static_cast<float>(CELL_SIZE_Y) / frameHeight;
    float scale = std::min(scaleX, scaleY);

    _electricSprite.setScale(scale, scale);

    float offsetX = (CELL_SIZE_X - (frameWidth_actual * scale)) / 2;
    float offsetY = (CELL_SIZE_Y - (frameHeight * scale)) / 2;
    _electricSprite.setPosition(realXpos + offsetX, realYPos + offsetY);

    window.draw(_electricSprite);
}

/**
 * @brief Displays the electric obstacles in the game scene.
 *
 * @param window The SFML window to render onto.
 */
void GameScene::displayElectrics(sf::RenderWindow& window)
{
    static int frameWidth = 0;
    static sf::Clock electricAnimationClock;

    if (electricAnimationClock.getElapsedTime().asSeconds() > 0.1f) {
        frameWidth += _textures["electric"].getSize().x / 4;
        if (
            frameWidth >= static_cast<int>(
                (_textures["electric"].getSize().x) - (_textures["electric"].getSize().x / 4)
            )
        ) {
            frameWidth = 0;
        }
        electricAnimationClock.restart();
    }

    for (const auto& electric : _obstacles) {
        displayElectric(window, electric, frameWidth);
    }
}

/**
 * @brief Displays a single coin in the game scene.
 *
 * @param window The SFML window to render onto.
 * @param coin The coinPos_t object representing the coin.
 * @param frameWidth The width of the animation frame.
 */
void GameScene::displayCoin(sf::RenderWindow& window, coinsPos_t coin, int frameWidth)
{
    int realYPos = MINIMUM_Y_POS + (coin.y_pos / 10.0) * (MAXIMUM_Y_POS - MINIMUM_Y_POS);
    int realXpos = 200 + (coin.x_pos * CELL_SIZE_X);

    int frameHeight = 171;
    int frameWidth_actual = 191;
    _coinSprite.setTextureRect(sf::IntRect(frameWidth, 0, frameWidth_actual, frameHeight));

    float scaleX = static_cast<float>(CELL_SIZE_X) / frameWidth_actual;
    float scaleY = static_cast<float>(CELL_SIZE_Y) / frameHeight;
    float scale = std::min(scaleX, scaleY) * 0.8f;

    _coinSprite.setScale(scale, scale);

    float offsetX = (CELL_SIZE_X - (frameWidth_actual * scale)) / 2;
    float offsetY = (CELL_SIZE_Y - (frameHeight * scale)) / 2;
    _coinSprite.setPosition(realXpos + offsetX, realYPos + offsetY);

    window.draw(_coinSprite);
}

/**
 * @brief Displays the coins in the game scene.
 *
 * @param window The SFML window to render onto.
 */
void GameScene::displayCoins(sf::RenderWindow& window)
{
    static int frameWidth = 0;
    static sf::Clock coinAnimationClock;

    if (coinAnimationClock.getElapsedTime().asSeconds() > 0.1f) {
        frameWidth += _textures["coin"].getSize().x / 6;
        if (
            frameWidth >= static_cast<int>(
                (_textures["coin"].getSize().x) - (_textures["coin"].getSize().x / 6)
            )
        ) {
            frameWidth = 0;
        }
        coinAnimationClock.restart();
    }

    for (const auto& coin : _coins) {
        displayCoin(window, coin, frameWidth);
    }
}

/**
 * @brief Displays a single player in the game scene.
 *
 * @param window The SFML window to render onto.
 * @param player The player_t object representing the player.
 * @param isMyPlayer Indicates if the player is the current user.
 * @param frameWidth The width of the animation frame.
 */
void GameScene::displayPlayer(sf::RenderWindow& window, player_t player, int frameWidth)
{
    int realYPos = MINIMUM_Y_POS + (player.y_pos / 10.0) * (MAXIMUM_Y_POS - MINIMUM_Y_POS);
    bool isMyPlayer = false;

    if (player.username == this->_username)
        isMyPlayer = true;

    int frameHeight = 134;
    int frameWidth_actual = 134;
    int row = 0;
    if (player.is_jetpack_on && player.y_pos <= 9) {
        row = 1;
    } else if (!player.is_jetpack_on && player.y_pos < 9) {
        row = 2;
    } else if (player.is_dead) {
        row = 3;
    } else {
        row = 0;
    }
    _playerSprite.setTextureRect(
        sf::IntRect(frameWidth, row * frameHeight, frameWidth_actual, frameHeight)
    );

    float scaleX = static_cast<float>(CELL_SIZE_X) / frameWidth_actual;
    float scaleY = static_cast<float>(CELL_SIZE_Y) / frameHeight;
    float scale = std::min(scaleX, scaleY) * 0.9f;

    _playerSprite.setScale(scale, scale);

    float offsetY = (CELL_SIZE_Y - (frameHeight * scale)) / 2;
    _playerSprite.setPosition(200, realYPos + offsetY);

    if (!isMyPlayer) {
        sf::Color color = _playerSprite.getColor();
        _playerSprite.setColor(sf::Color(color.r, color.g, color.b, 127));
    } else {
        sf::Color color = _playerSprite.getColor();
        _playerSprite.setColor(sf::Color(color.r, color.g, color.b, 255));
    }

    _usernameText.setString((strcmp(player.username, "") == 0) ? "No Name" : player.username);

    sf::FloatRect textBounds = _usernameText.getGlobalBounds();
    _usernameText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    _usernameText.setPosition(
        _playerSprite.getPosition().x + _playerSprite.getGlobalBounds().width / 2,
        _playerSprite.getPosition().y - textBounds.height
    );

    window.draw(_playerSprite);
    window.draw(_usernameText);
}

/**
 * @brief Displays the players in the game scene.
 *
 * @param window The SFML window to render onto.
 */
void GameScene::displayPlayers(sf::RenderWindow& window)
{
    static int frameWidth = 0;
    static sf::Clock playerAnimationClock;

    if (playerAnimationClock.getElapsedTime().asSeconds() > 0.1f) {
        frameWidth += _textures["player"].getSize().x / 4;
        if (frameWidth >= static_cast<int>(_textures["player"].getSize().x) - frameWidth)
            frameWidth = 0;
        playerAnimationClock.restart();
    }

    for (const auto& player : _players) {
        displayPlayer(window, player, frameWidth);
    }
}

/**
 * @brief Sets the players in the game scene.
 *
 * @param players The vector of player_t objects to set.
 */
void GameScene::setPlayers(std::vector<player_t> players)
{
    if (players.empty())
        return;

    _players.swap(players);
}

/**
 * @brief Sets the coins in the game scene.
 *
 * @param coins The vector of coinsPos_t objects to set.
 */
void GameScene::setCoins(std::vector<coinsPos_t> coins)
{
    if (coins.empty())
        return;

    _coins.swap(coins);
}

/**
 * @brief Sets the obstacles in the game scene.
 *
 * @param obstacles The vector of obstacle_t objects to set.
 */
void GameScene::setObstacles(std::vector<obstacle_t> obstacles)
{
    if (obstacles.empty())
        return;

    _obstacles.swap(obstacles);
}

/**
 * @brief Sets the username of the player.
 *
 * @param username The username to set.
 */
void GameScene::setUsername(const std::string& username)
{
    _username = username;
}

/**
 * @brief Gets the game end status.
 *
 * @return True if the game has ended, false otherwise.
 */
bool GameScene::getGameEnd() const
{
    return _gameEnded;
}

/**
 * @brief Sets the game end status.
 *
 * @param gameEnd The new game end status.
 */
void GameScene::setGameEnd(bool gameEnd)
{
    _gameEnded = gameEnd;
}
