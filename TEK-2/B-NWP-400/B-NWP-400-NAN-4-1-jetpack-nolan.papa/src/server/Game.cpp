/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Game
*/

#include <chrono>
#include <cmath>
#include <thread>
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

#include "Game.hpp"
#include "entities/ElectricEntity.hpp"
#include "entities/CoinEntity.hpp"

/**
 * @brief Constructs a Game instance with a given map.
 *
 * @param map The initial game map, represented as a 2D vector of IEntity pointers.
 */
Game::Game(std::vector<std::vector<std::shared_ptr<IEntity>>> &map, int port, bool debug)
{
    _map = map;
    _players = {};
    _lastUpdateTime = std::chrono::system_clock::now();
    _communication.startServer(port);
    _communication.setDebugMode(debug);
}

/**
 * @brief Destructor for the Game class.
 *
 * Cleans up the players vector.
 */
Game::~Game()
{
    for (auto line : _map) {
        line.clear();
        line.shrink_to_fit();
    }
    _map.clear();
    _map.shrink_to_fit();
    _players.clear();
    _players.shrink_to_fit();
}

/**
 * @brief Gets the current game map.
 *
 * @return The map as a 2D vector of IEntity pointers.
 */
std::vector<std::vector<std::shared_ptr<IEntity>>> Game::getMap()
{
    return _map;
}

/**
 * @brief Gets the list of players in the game.
 *
 * @return A vector of shared pointers to Player instances.
 */
std::vector<std::shared_ptr<Player>> Game::getPlayers()
{
    return _players;
}

/**
 * @brief Sets a new map for the game.
 *
 * @param map The new game map.
 */
void Game::setMap(std::vector<std::vector<std::shared_ptr<IEntity>>> map)
{
    _map = map;
}

/**
 * @brief Sets the list of players in the game.
 *
 * @param players A vector of shared pointers to Player instances.
 */
void Game::setPlayers(std::vector<std::shared_ptr<Player>> players)
{
    _players = players;
}

/**
 * @brief Adds a player to the game.
 *
 * @param player A shared pointer to the Player to add.
 */
void Game::addPlayer(std::shared_ptr<Player> player)
{
    _players.push_back(player);
}

/**
 * @brief Removes a player from the game.
 *
 * @param player A shared pointer to the Player to remove.
 */
void Game::removePlayer(std::shared_ptr<Player> player)
{
    for (auto it = _players.begin(); it != _players.end(); it++) {
        if ((*it)->getId() == player->getId()) {
            _players.erase(it);
            break;
        }
    }
}

/**
 * @brief Runs the game loop, updating the game state continuously.
 */
void Game::run()
{
    while (true) {
        removeLeftPlayers();

        if (_players.size() < NB_CLIENTS) {
            Player newPlayer = _communication.getNewClient();
            if (newPlayer.getId() != -1)
                addPlayer(std::make_shared<Player>(newPlayer));
        }

        auto clientsData = _communication.getClientsData();
        for (auto& clientData : clientsData) {
            auto player = std::find_if(_players.begin(), _players.end(),
                [&clientData](const std::shared_ptr<Player>& player) {
                    return player->getId() == clientData.getId();
                });
            if (player != _players.end()) {
                for (auto input : clientData.getInputs()) {
                    if (input == CHANGE_NAME) {
                        (*player)->setUsername(clientData.getName());
                    }
                    if (input == FLY) {
                        (*player)->setJetpackActivated(!(*player)->isJetpackActivated());
                    }
                }
            }
        }

        if (!_communication.getGameStarted())
            continue;

        GameState gameState(_players, _map);
        _communication.sendGameState(gameState);

        update();
        if (hasReachedEnd()) {
            _communication.sendGameEnd();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

/**
 * @brief Removes players that have disconnected from the game.
 */
void Game::removeLeftPlayers()
{
    for (auto it = _players.begin(); it != _players.end();) {
        if (_communication.isPlayerGone((*it)->getId())) {
            it = _players.erase(it);
        } else {
            ++it;
        }
    }
}

/**
 * @brief Updates the game state, including physics and interactions.
 */
void Game::update()
{
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = currentTime - _lastUpdateTime;
    double deltaTime = elapsed.count();
    _lastUpdateTime = currentTime;

    if (deltaTime > 0.1)
        deltaTime = 0.1;

    for (auto player : _players) {
        if (!player->isAlive())
            return;
    }
    updatePhysics(deltaTime);
    updateInteractions();
}

/**
 * @brief Updates the physics for all players.
 *
 * @param deltaTime The time elapsed since the last update.
 */
void Game::updatePhysics(double deltaTime)
{
    for (auto player : _players) {
        if (!player->isAlive())
            continue;

        auto velocity = player->getVelocity();

        if (player->isJetpackActivated())
            player->setVelocity({velocity.first, velocity.second - JETPACK_FORCE * deltaTime});
        else
            player->setVelocity({velocity.first, velocity.second + GRAVITY * deltaTime});

        velocity = player->getVelocity();
        player->setVelocity({FORWARD_VELOCITY, velocity.second});

        velocity = player->getVelocity();
        if (velocity.second > MAX_VELOCITY_Y)
            player->setVelocity({velocity.first, MAX_VELOCITY_Y});
        else if (velocity.second < -MAX_VELOCITY_Y)
            player->setVelocity({velocity.first, -MAX_VELOCITY_Y});

        player->updatePosition(deltaTime);

        auto pos = player->getPos();
        if (!isValidPosition(pos)) {
            if (pos.second < 0) {
                player->setPos({pos.first, 0});
                player->setVelocity({velocity.first, 0});
            } else if (pos.second > _map.size()) {
                player->setPos({pos.first, static_cast<double>(_map.size() - 1)});
                player->setVelocity({velocity.first, 0});
            }
        }
    }
}

/**
 * @brief Handles interactions between players and entities on the map.
 */
void Game::updateInteractions()
{
    for (auto player : _players) {
        if (!player->isAlive())
            continue;

        auto overlappingCells = getOverlappingCells(player->getPos());

        for (auto& cell : overlappingCells) {
            if (
                cell.first < 0 ||
                cell.second < 0 ||
                cell.second >= static_cast<int>(_map.size()) ||
                cell.first >= static_cast<int>(_map[0].size())
            )
                continue;

            auto entity = _map[cell.second][cell.first];
            entity->onInteract(player);
        }
    }
}

/**
 * @brief Retrieves the map cells overlapping with the given position.
 *
 * @param pos The position of the player as a pair of doubles (x, y).
 * @return A vector of integer pairs representing the overlapping cells.
 */
std::vector<std::pair<int, int>> Game::getOverlappingCells(std::pair<double, double> pos)
{
    std::vector<std::pair<int, int>> cells;
    int baseX = static_cast<int>(pos.first);
    int baseY = static_cast<int>(pos.second);
    double fractionX = pos.first - baseX;
    double fractionY = pos.second - baseY;

    cells.push_back({baseX, baseY});

    if (fractionX > 0.5) cells.push_back({baseX + 1, baseY});
    if (fractionY > 0.5) cells.push_back({baseX, baseY + 1});
    if (fractionX > 0.5 && fractionY > 0.5) cells.push_back({baseX + 1, baseY + 1});

    return cells;
}

/**
 * @brief Checks if a given position is valid within the game boundaries.
 *
 * @param pos The position to check.
 * @return True if the position is valid, false otherwise.
 */
bool Game::isValidPosition(std::pair<double, double> pos)
{
    return pos.second >= 0 && pos.second < _map.size();
}

/**
 * @brief Checks if the game has reached its end condition.
 *
 * @return True if the game has ended, false otherwise.
 */
bool Game::hasReachedEnd()
{
    if (_players.size() < 2)
        return true;

    for (auto player : _players) {
        if (!player->isAlive())
            return true;
    }

    int xEnd = _map[0].size() - 1;
    for (auto player : _players) {
        if (player->getPos().first >= xEnd)
            return true;
    }
    return false;
}
