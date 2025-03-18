/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** is_inv_full
*/

#include "rpg_header.h"

bool is_inv_full(gamedata_t *game)
{
    backpack_t *back = game->inventory->backpack;
    int nb = 0;

    while (back != NULL) {
        nb += 1;
        back = back->next;
    }
    if (nb == INV_SIZE)
        return (true);
    return (false);
}
