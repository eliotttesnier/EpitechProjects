/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** credits_display
*/

#include "rpg_header.h"

void credits_display(gamedata_t *game)
{
    sfRenderWindow_clear(game->window->window, sfBlack);
    sfRenderWindow_drawSprite(game->window->window,
        game->menu->creditmenu->back->sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->menu->creditmenu->display->sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->menu->creditmenu->backbutt->sprite->sprite, NULL);
    sfRenderWindow_display(game->window->window);
}
