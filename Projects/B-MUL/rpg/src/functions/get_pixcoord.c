/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** get_pixcoord
*/

#include "rpg_header.h"

sfVector2f get_pixcoord(gamedata_t *game)
{
    sfRenderWindow *win = game->window->window;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win);
    sfView *view = (sfView *)sfRenderWindow_getView(game->window->window);

    return (sfRenderWindow_mapPixelToCoords(win, mouse, view));
}
