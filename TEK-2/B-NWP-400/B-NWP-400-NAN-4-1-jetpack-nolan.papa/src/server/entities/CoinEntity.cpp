/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** CoinEntity
*/

#include "CoinEntity.hpp"

/**
 * @brief Constructs a CoinEntity at the given position.
 *
 * @param pos The initial position of the coin.
 */
CoinEntity::CoinEntity(std::pair<int, int> pos)
{
    _pos = pos;
    _asset = "coin";
}

/**
 * @brief Handles interaction with a player by allowing them to collect the coin.
 *
 * @param player A shared pointer to the Player interacting with the coin.
 */
void CoinEntity::onInteract(std::shared_ptr<Player> player)
{
    player->collectCoin(std::make_shared<CoinEntity>(_pos));
}
