/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** ElectricEntity
*/

#include "ElectricEntity.hpp"

/**
 * @brief Constructs an ElectricEntity at the given position.
 *
 * @param pos The initial position of the electric entity.
 */
ElectricEntity::ElectricEntity(std::pair<int, int> pos)
{
    _pos = pos;
    _asset = "electric";
}

/**
 * @brief Handles interaction with a player, causing them to die upon contact.
 *
 * @param player A shared pointer to the Player interacting with the entity.
 */
void ElectricEntity::onInteract(std::shared_ptr<Player> player)
{
    player->die();
}
