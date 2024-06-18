/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_movement
*/

#include "rpg_header.h"

void free_movement(movement_t *move)
{
    sfClock_destroy(move->clock);
    free(move);
}
