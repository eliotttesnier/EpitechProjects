/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** insert_hang
*/

#include "rpg_header.h"

void add_in_back_pos(gamedata_t *game, item_t *i, sprite_t *s, backpack_t *b)
{
    backpack_t *new = malloc(sizeof(backpack_t) * 1);
    backpack_t *tmp;

    new->item = i;
    new->sprite = s;
    if (game->inventory->backpack == b) {
        new->next = game->inventory->backpack;
        game->inventory->backpack = new;
        return;
    }
    for (tmp = game->inventory->backpack; tmp->next != b; tmp = tmp->next);
    new->next = tmp->next;
    tmp->next = new;
}

static void put_to_equip(gamedata_t *game, int stf)
{
    hanging_t *hang = game->inventory->hanging;
    item_t *itmp = NULL;
    sprite_t *stmp = NULL;

    add_stats(game, hang->item);
    if (game->inventory->equipment->equiped[stf] != NULL) {
        itmp = game->inventory->equipment->equiped[stf];
        stmp = game->inventory->equipment->sprites[stf];
    }
    game->inventory->equipment->equiped[stf] = hang->item;
    game->inventory->equipment->sprites[stf] = hang->sprite;
    game->inventory->hanging = NULL;
    if (itmp != NULL) {
        remove_stats(game, itmp);
        add_in_back_pos(game, itmp, stmp, NULL);
    }
}

void insert_in_equip(gamedata_t *game, int stf)
{
    hanging_t *hang = game->inventory->hanging;

    if (hang->item->id >= 0 && hang->item->id <= 14 && stf == WEAPON)
        put_to_equip(game, stf);
    if (hang->item->id >= 15 && hang->item->id <= 19 && stf == HELMET)
        put_to_equip(game, stf);
    if (hang->item->id >= 20 && hang->item->id <= 24 && stf == CHEST)
        put_to_equip(game, stf);
    if (hang->item->id >= 25 && hang->item->id <= 29 && stf == GLOVES)
        put_to_equip(game, stf);
    if (hang->item->id >= 30 && hang->item->id <= 34 && stf == BOOTS)
        put_to_equip(game, stf);
    remove_from_hang(game);
}

void insert_in_back(gamedata_t *game, backpack_t *back)
{
    add_in_back_pos(game, game->inventory->hanging->item,
        game->inventory->hanging->sprite, back);
    free(game->inventory->hanging);
    game->inventory->hanging = NULL;
}
