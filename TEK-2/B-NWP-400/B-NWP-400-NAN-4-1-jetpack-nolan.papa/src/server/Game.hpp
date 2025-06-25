/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <vector>
#include <chrono>

#include "Player.hpp"
#include "entities/IEntity.hpp"
#include "communication/Communication.hpp"

class Game {
    private:
        std::vector<std::vector<std::shared_ptr<IEntity>>> _map;
        std::vector<std::shared_ptr<Player>> _players;
        std::chrono::time_point<std::chrono::system_clock> _lastUpdateTime;

        // Physics constants
        const double GRAVITY = 12.0;
        const double JETPACK_FORCE = 15.0;
        const double FORWARD_VELOCITY = 2.0;
        const double MAX_VELOCITY_Y = 8.0;

        Communication _communication;

    public:
        Game(std::vector<std::vector<std::shared_ptr<IEntity>>> &map, int port, bool debug);
        ~Game();

        // Getters
        std::vector<std::vector<std::shared_ptr<IEntity>>> getMap();
        std::vector<std::shared_ptr<Player>> getPlayers();

        // Setters
        void setMap(std::vector<std::vector<std::shared_ptr<IEntity>>> map);
        void setPlayers(std::vector<std::shared_ptr<Player>> players);

        // Methods
        void addPlayer(std::shared_ptr<Player> player);
        void removePlayer(std::shared_ptr<Player> player);
        void run();
        void update();
        void updatePhysics(double deltaTime);
        void updateInteractions();
        void removeLeftPlayers();
        bool hasReachedEnd();

        // Helper functions
        std::vector<std::pair<int, int>> getOverlappingCells(std::pair<double, double> pos);
        bool isValidPosition(std::pair<double, double> pos);
};

#endif /* !GAME_HPP_ */
