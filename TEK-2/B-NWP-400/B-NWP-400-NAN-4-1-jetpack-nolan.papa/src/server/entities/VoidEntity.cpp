/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** VoidEntity
*/

#include "VoidEntity.hpp"

/**
 * @brief Constructs a VoidEntity at the given position.
 *
 * @param pos The initial position of the void entity.
 */
VoidEntity::VoidEntity(std::pair<int, int> pos)
{
    _pos = pos;
    _asset = "void";
}

/**
 * @brief Handles interaction with a player. This entity has no effect.
 *
 * @param player A shared pointer to the Player interacting with the entity.
 */
void VoidEntity::onInteract(std::shared_ptr<Player> player)
{
    (void)player;
}
