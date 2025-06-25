/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-nolan.papa
** File description:
** AEntity
*/

#include <utility>

#include "AEntity.hpp"

/**
 * @brief Sets the position of the entity.
 *
 * @param pos The new position as a pair of integers (x, y).
 */
void AEntity::setPos(std::pair<double, double> pos)
{
    _pos = pos;
}

/**
 * @brief Gets the current position of the entity.
 *
 * @return The position as a pair of integers (x, y).
 */
std::pair<double, double> AEntity::getPos()
{
    return _pos;
}
