/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** add_to_inv
*/

#include "rpg_header.h"

void add_to_inv(gamedata_t *game, item_t *item)
{
    backpack_t *new = malloc(sizeof(backpack_t) * 1);
    backpack_t *tmp;

    new->item = item;
    if (item == NULL)
        return;
    new->sprite = create_sprite(item->asset_path, (sfIntRect){0, 0, 100, 100});
    sfSprite_setScale(new->sprite->sprite, (sfVector2f){0.25, 0.25});
    new->next = NULL;
    if (game->inventory->backpack == NULL) {
        game->inventory->backpack = new;
        return;
    }
    for (tmp = game->inventory->backpack; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
}
