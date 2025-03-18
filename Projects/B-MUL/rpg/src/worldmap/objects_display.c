/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** objects_display
*/

#include "rpg_header.h"

void display_chests_front(gamedata_t *game)
{
    for (chest_t *tmp = game->obj->chests; tmp != NULL; tmp = tmp->next) {
        if (!is_chest_visible(game, tmp))
            continue;
        if (game->entity->player->position.y + 10 <= tmp->position.y +
            (tmp->sprite->rect.height * 0.5)) {
            sfSprite_setTextureRect(tmp->sprite->sprite, tmp->sprite->rect);
            sfRenderWindow_drawSprite(game->window->window,
                tmp->sprite->sprite, NULL);
        }
    }
}

void display_objects_front(gamedata_t *game)
{
    display_chests_front(game);
}

void display_chests_back(gamedata_t *game)
{
    for (chest_t *tmp = game->obj->chests; tmp != NULL; tmp = tmp->next) {
        if (!is_chest_visible(game, tmp))
            continue;
        if (game->entity->player->position.y + 10 > tmp->position.y +
            (tmp->sprite->rect.height * 0.5)) {
            sfSprite_setTextureRect(tmp->sprite->sprite, tmp->sprite->rect);
            sfRenderWindow_drawSprite(game->window->window,
                tmp->sprite->sprite, NULL);
        }
    }
}

void display_objects_back(gamedata_t *game)
{
    display_chests_back(game);
}
