/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** over_display
*/

#include "rpg_header.h"

void over_display(gamedata_t *game)
{
    sfRenderWindow_clear(game->window->window, sfBlack);
    sfRenderWindow_drawSprite(game->window->window,
        game->hud->gameover->sprite, NULL);
    sfRenderWindow_display(game->window->window);
}
