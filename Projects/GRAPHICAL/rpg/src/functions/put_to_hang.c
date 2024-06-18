/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** put_to_hang
*/

#include "rpg_header.h"

void remove_in_back(gamedata_t *game, backpack_t *back)
{
    backpack_t *tmp = game->inventory->backpack;

    if (tmp == back) {
        game->inventory->backpack = game->inventory->backpack->next;
        return;
    }
    while (tmp->next != NULL) {
        if (tmp->next == back) {
            tmp->next = tmp->next->next;
            return;
        }
        tmp = tmp->next;
    }
}

void put_equip_to_hang(gamedata_t *game, equipment_t *equip, stuff_t stf,
    sfVector2f pix)
{
    game->inventory->hanging = malloc(sizeof(hanging_t) * 1);
    game->inventory->hanging->pos = pix;
    game->inventory->hanging->item = equip->equiped[stf];
    remove_stats(game, equip->equiped[stf]);
    game->inventory->hanging->sprite = equip->sprites[stf];
    equip->equiped[stf] = NULL;
    equip->sprites[stf] = NULL;
}

void put_to_hang(gamedata_t *game, backpack_t *back, sfVector2f pix)
{
    game->inventory->hanging = malloc(sizeof(hanging_t) * 1);
    game->inventory->hanging->pos = pix;
    game->inventory->hanging->item = back->item;
    game->inventory->hanging->sprite = back->sprite;
    remove_in_back(game, back);
}
