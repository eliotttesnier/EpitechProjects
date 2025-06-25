/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** DisplayGame
*/

#ifndef GAMESCENE_HPP_
    #define GAMESCENE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <chrono>
#include <string>
#include <filesystem>
#include "Display.hpp"
#include "entities/AEntity.hpp"

class GameScene {
    public:
        // Constructor
        GameScene(std::string username);
        ~GameScene();

        // Method
        void handleEvents(Display& display);
        void update();
        void display(sf::RenderWindow& window);
        void stopSounds();

        void setUsername(const std::string& username);

        void setPlayers(std::vector<player_t> players);
        void setCoins(std::vector<coinsPos_t> coins);
        void setObstacles(std::vector<obstacle_t> obstacles);

        bool getGameEnd() const;
        void setGameEnd(bool gameEnd);

    private:
        // Variable
        std::string _username;
        std::vector<player_t> _players;
        // std::vector<player_t> _prevPlayers;
        std::vector<coinsPos_t> _coins;
        // std::vector<coinsPos_t> _prevCoins;
        std::vector<obstacle_t> _obstacles;

        std::map<std::string, sf::Texture> _textures;
        sf::Texture _backgroundTexture;
        sf::Sprite _backgroundSprite_first;
        sf::Sprite _backgroundSprite_second;
        sf::Font _font;

        sf::Sprite _playerSprite;
        sf::Sprite _coinSprite;
        sf::Sprite _electricSprite;

        sf::Music _themeMusic;
        sf::SoundBuffer _coinPickupBuffer;
        sf::SoundBuffer _zapperDeathBuffer;
        sf::SoundBuffer _jetpackStartBuffer;
        sf::SoundBuffer _jetpackLoopBuffer;
        sf::SoundBuffer _jetpackStopBuffer;
        sf::SoundBuffer _dogLaughBuffer;
        sf::Sound _coinPickupSound;
        sf::Sound _zapperDeathSound;
        sf::Sound _jetpackStartSound;
        sf::Sound _jetpackLoopSound;
        sf::Sound _jetpackStopSound;
        sf::Sound _dogLaughSound;
        bool _isJetpackActive;
        int _prevCoinCount;
        bool _musicStarted;
        bool _dogLaughPlayed;

        bool _gridDebug;
        bool _gameEnded;
        bool _isWinner;
        sf::Sprite _winSprite;
        sf::Sprite _loseSprite;

        sf::Text _usernameText;
        sf::Text _usernameTextHUD;
        sf::Text _coinsTextHUD;

        std::vector<sf::Texture> _dogLaughFrames;
        std::chrono::time_point<std::chrono::steady_clock> _gameEndTime;
        float _videoDuration;
        int _currentFrameIndex;
        sf::Sprite _videoSprite;

        void displayHUD(sf::RenderWindow& window);
        void displayDebug(sf::RenderWindow& window);
        void displayGameEndScreen(sf::RenderWindow& window);

        void displayPlayers(sf::RenderWindow& window);
        void displayPlayer(sf::RenderWindow& window, player_t player, int frameWidth);

        void displayCoins(sf::RenderWindow& window);
        void displayCoin(sf::RenderWindow& window, coinsPos_t coin, int frameWidth);

        void displayElectrics(sf::RenderWindow& window);
        void displayElectric(sf::RenderWindow& window, obstacle_t electric, int frameWidth);

        void loadTextures();
        void loadSounds();
        void updateSounds();
        void initBackground();

        void checkWinners();
        void loadDogLaughFrames();
};

#endif /* !GAMESCENE_HPP_ */
