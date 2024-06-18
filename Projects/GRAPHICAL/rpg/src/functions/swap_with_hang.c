/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** swap_with_hang
*/

#include "rpg_header.h"

void swap_with_hang(gamedata_t *game, backpack_t *back)
{
    hanging_t *hang = game->inventory->hanging;
    item_t *itmp;
    sprite_t *stmp;

    itmp = hang->item;
    stmp = hang->sprite;
    hang->item = back->item;
    hang->sprite = back->sprite;
    back->item = itmp;
    back->sprite = stmp;
}
