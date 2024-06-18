/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** remove_from_hang
*/

#include "rpg_header.h"

void add_in_back(gamedata_t *game, item_t *item, sprite_t *sprite)
{
    backpack_t *new = malloc(sizeof(backpack_t) * 1);
    backpack_t *tmp;

    new->item = item;
    new->sprite = sprite;
    new->next = NULL;
    if (game->inventory->backpack == NULL) {
        game->inventory->backpack = new;
        return;
    }
    for (tmp = game->inventory->backpack; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
}

void remove_from_hang(gamedata_t *game)
{
    if (game->inventory->hanging == NULL)
        return;
    add_in_back(game, game->inventory->hanging->item,
        game->inventory->hanging->sprite);
    free(game->inventory->hanging);
    game->inventory->hanging = NULL;
}
