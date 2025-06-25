/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** Player
*/

#include <cmath>
#include <utility>
#include <string>
#include <vector>

#include "Player.hpp"

/**
 * @brief Initializes a new player with a username, ID, and default properties.
 *
 * The player's position is set to (0.0, 0.0), velocity to (0.0, 0.0), and the player is alive by default. 
 * The jetpack is deactivated and no coins are collected initially.
 *
 * @param username The player's username.
 * @param id The player's unique ID.
 */
Player::Player(std::string username, int id)
{
    _username = username;
    _id = id;
    _isAlive = true;
    _isJetpackActivated = false;
    _pos = {0.0, 0.0};
    _velocity = {0.0, 0.0};
    _coinsCollected = {};
}

/**
 * @brief Sets the player's position.
 *
 * Updates the player's position to the provided coordinates.
 *
 * @param pos The new position of the player.
 */
void Player::setPos(std::pair<double, double> pos)
{
    _pos = pos;
}

/**
 * @brief Sets the player's username.
 *
 * Updates the player's username to the provided string.
 *
 * @param username The new username of the player.
 */
void Player::setUsername(std::string username)
{
    _username = username;
}

/**
 * @brief Sets the player's ID.
 *
 * Updates the player's unique ID.
 *
 * @param id The new ID for the player.
 */
void Player::setId(int id)
{
    _id = id;
}

/**
 * @brief Sets the player's alive status.
 *
 * Updates whether the player is alive or not.
 *
 * @param isAlive True if the player is alive, false if dead.
 */
void Player::setAlive(bool isAlive)
{
    _isAlive = isAlive;
}

/**
 * @brief Sets the player's jetpack activation status.
 *
 * Updates whether the player's jetpack is activated or not.
 *
 * @param isJetpackActivated True if the jetpack is activated, false otherwise.
 */
void Player::setJetpackActivated(bool isJetpackActivated)
{
    _isJetpackActivated = isJetpackActivated;
}

/**
 * @brief Sets the player's velocity.
 *
 * Updates the player's velocity to the specified values for the x and y axes.
 *
 * @param velocity The new velocity of the player.
 */
void Player::setVelocity(std::pair<double, double> velocity)
{
    _velocity = velocity;
}

/**
 * @brief Gets the player's current position.
 *
 * Returns the current position of the player as a pair of x and y coordinates.
 *
 * @return A pair of doubles representing the player's position.
 */
std::pair<double, double> Player::getPos()
{
    return _pos;
}

/**
 * @brief Gets the player's position in terms of grid coordinates.
 *
 * Converts the player's floating-point position to integer grid coordinates by rounding the values.
 *
 * @return A pair of integers representing the player's grid position.
 */
std::pair<int, int> Player::getGridPos()
{
    return {
        static_cast<int>(std::round(_pos.first)),
        static_cast<int>(std::round(_pos.second))
    };
}

/**
 * @brief Gets the player's username.
 *
 * Returns the current username of the player.
 *
 * @return A string representing the player's username.
 */
std::string Player::getUsername()
{
    return _username;
}

/**
 * @brief Gets the player's unique ID.
 *
 * Returns the player's ID.
 *
 * @return The player's ID.
 */
int Player::getId()
{
    return _id;
}

/**
 * @brief Checks if the player is alive.
 *
 * Returns whether the player is currently alive.
 *
 * @return True if the player is alive, false if dead.
 */
bool Player::isAlive()
{
    return _isAlive;
}

/**
 * @brief Checks if the player's jetpack is activated.
 *
 * Returns whether the player's jetpack is currently active.
 *
 * @return True if the jetpack is activated, false otherwise.
 */
bool Player::isJetpackActivated()
{
    return _isJetpackActivated;
}

/**
 * @brief Gets the list of coins collected by the player.
 *
 * Returns a vector of shared pointers to the coins the player has collected.
 *
 * @return A vector of shared pointers to the collected coins.
 */
std::vector<std::shared_ptr<CoinEntity>> Player::getCoinsCollected()
{
    return _coinsCollected;
}

/**
 * @brief Gets the player's current velocity.
 *
 * Returns the player's current velocity as a pair of x and y components.
 *
 * @return A pair of doubles representing the player's velocity.
 */
std::pair<double, double> Player::getVelocity()
{
    return _velocity;
}

/**
 * @brief Collects a coin for the player.
 *
 * Adds the specified coin to the player's collected coins if it has not been collected already.
 *
 * @param coin A shared pointer to the coin entity to collect.
 */
void Player::collectCoin(std::shared_ptr<CoinEntity> coin)
{
    std::pair<double, double> coinPos = coin->getPos();

    for (auto &c : _coinsCollected) {
        if (c->getPos() == coinPos)
            return;
    }

    _coinsCollected.push_back(coin);
}

/**
 * @brief Marks the player as dead.
 *
 * Sets the player's alive status to false.
 */
void Player::die()
{
    _isAlive = false;
}

/**
 * @brief Respawns the player at the starting position.
 *
 * Resets the player's alive status, velocity, and position to initial values.
 */
void Player::respawn()
{
    _isAlive = true;
    _velocity = {0.0, 0.0};
    _pos.second = 0.0;
}

/**
 * @brief Applies a force to the player's velocity.
 *
 * Adds the specified force to the player's velocity in both the x and y directions.
 *
 * @param x The force applied in the x direction.
 * @param y The force applied in the y direction.
 */
void Player::applyForce(double x, double y)
{
    _velocity.first += x;
    _velocity.second += y;
}

/**
 * @brief Updates the player's position based on velocity and elapsed time.
 *
 * Adjusts the player's position according to its current velocity and the elapsed time since the last update.
 * Includes slight velocity damping for realism.
 *
 * @param deltaTime The time that has passed since the last update (in seconds).
 */
void Player::updatePosition(double deltaTime)
{
    _pos.first += _velocity.first * deltaTime;
    _pos.second += _velocity.second * deltaTime;

    // Slight damping (0.5% per frame)
    _velocity.second *= 0.995;
    _velocity.first = 0.0;
    if (_pos.second > 9.0) {
        _pos.second = 9.0;
        _velocity.second = 0.0;
    }
    if (_pos.second < 0.0) {
        _pos.second = 0.0;
        _velocity.second = 0.0;
    }
}
