/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** toggle_fullscreen
*/

#include "rpg_header.h"

void toggle_fullscreen(void *gamedata)
{
    gamedata_t *game = (gamedata_t *)gamedata;

    game->window->fullscreen = !game->window->fullscreen;
    if (game->window->fullscreen) {
        sfRenderWindow_close(game->window->window);
        game->window->window = sfRenderWindow_create(
            sfVideoMode_getDesktopMode(), "The Legend of Damopies",
            sfFullscreen, NULL);
        sfRenderWindow_setIcon(game->window->window, 100, 100,
        game->window->icon);
        sfRenderWindow_setFramerateLimit(game->window->window, FRAMERATE);
    } else {
        sfRenderWindow_close(game->window->window);
        game->window->window = sfRenderWindow_create(game->window->resolution,
        "The Legend of Damopies", sfResize | sfClose, NULL);
        sfRenderWindow_setIcon(game->window->window, 100, 100,
        game->window->icon);
        sfRenderWindow_setFramerateLimit(game->window->window, FRAMERATE);
    }
}
