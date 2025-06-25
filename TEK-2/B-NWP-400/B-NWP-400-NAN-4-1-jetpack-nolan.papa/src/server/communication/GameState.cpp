/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** GameState
*/

#include <vector>

#include "GameState.hpp"

/**
 * @brief Constructs a GameState object.
 * 
 * Initializes the game state by processing the provided players and map data.
 * 
 * @param players A vector of shared pointers to Player objects representing the players in the game.
 * @param map A 2D vector of shared pointers to IEntity objects representing the game map.
 * 
 * The constructor extracts player information (position, coins collected, status, etc.)
 * and identifies entities in the map (coins and electric obstacles), storing their positions.
 */
GameState::GameState(std::vector<std::shared_ptr<Player>> players,
                     std::vector<std::vector<std::shared_ptr<IEntity>>> map)
{
    for (auto &player : players) {
        player_t playerStruct{};
        std::memset(&playerStruct, 0, sizeof(playerStruct));
        playerStruct.y_pos = player->getPos().second;
        std::strncpy(
            playerStruct.username,
            player->getUsername().c_str(),
            sizeof(playerStruct.username) - 1
        );
        playerStruct.coins_collected = player->getCoinsCollected().size();
        playerStruct.is_dead = !player->isAlive();
        playerStruct.is_jetpack_on = player->isJetpackActivated();
        _players.push_back(playerStruct);
        _playerPosX = player->getPos().first;
        _playersEntities[player->getId()] = player;
    }
    for (auto &row : map) {
        for (auto &entity : row) {
            if (std::dynamic_pointer_cast<CoinEntity>(entity)) {
                coinsPos_t coin{};
                coin.x_pos = entity->getPos().first;
                coin.y_pos = entity->getPos().second;
                _coins.push_back(coin);
            } else if (std::dynamic_pointer_cast<ElectricEntity>(entity)) {
                obstacle_t obstacle{};
                obstacle.x_pos = entity->getPos().first;
                obstacle.y_pos = entity->getPos().second;
                _electricity.push_back(obstacle);
            }
        }
    }
}

/**
 * @brief Destructor for the GameState class.
 * 
 * Cleans up any resources used by the GameState object.
 */
GameState::~GameState()
{
    _players.clear();
    _players.shrink_to_fit();
    _coins.clear();
    _coins.shrink_to_fit();
    _electricity.clear();
    _electricity.shrink_to_fit();
    _playersEntities.clear();
}

/**
 * @brief Retrieves the list of players in the game state.
 * 
 * @return A vector of player_t structures containing player information such as position,
 *         coins collected, status (alive or dead), and jetpack activation state.
 */
std::vector<player_t> GameState::getPlayers() const
{
    return _players;
}

/**
 * @brief Retrieves the list of coin positions in the game state.
 * 
 * @return A vector of coinsPos_t structures containing the positions of coins on the map.
 */
std::vector<coinsPos_t> GameState::getCoins()
{
    for (auto &coin : _coins) {
        coin.x_pos = coin.x_pos - (_playerPosX);
    }
    return _coins;
}

/**
 * @brief Retrieves the list of electric obstacle positions in the game state.
 * 
 * @return A vector of obstacle_t structures containing the positions of electric obstacles on the map.
 */
std::vector<obstacle_t> GameState::getElectricity()
{
    for (auto &electric : _electricity) {
        electric.x_pos = electric.x_pos - (_playerPosX);
    }
    return _electricity;
}

/**
 * @brief Retrieves the list of coins not collected by a specific player.
 * 
 * @param id The ID of the player whose uncollected coins are to be retrieved.
 * @return A vector of coinsPos_t structures containing the positions of coins not collected by the specified player.
 */
std::vector<coinsPos_t> GameState::getPlayerNotCollectedCoins(int id)
{
    std::vector<coinsPos_t> coins;
    bool found = false;

    if (_playersEntities.find(id) == _playersEntities.end())
        return getCoins();

    for (auto &coin : _coins) {
        found = false;
        for (auto &collectedCoin : _playersEntities.at(id)->getCoinsCollected()) {
            if (
                collectedCoin->getPos().first == coin.x_pos &&
                collectedCoin->getPos().second == coin.y_pos
            ) {
                found = true;
                break;
            }
        }
        if (found)
            continue;
        coins.push_back(coin);
    }
    for (auto &coin : coins) {
        coin.x_pos = coin.x_pos - (_playerPosX);
    }
    return coins;
}
