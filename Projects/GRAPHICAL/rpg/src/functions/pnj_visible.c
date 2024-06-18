/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** pnj_visible
*/

#include "rpg_header.h"

bool is_pnj_visible(gamedata_t *game, pnj_t *pnj)
{
    sfVector2f center = sfView_getCenter(game->window->view);

    if (abs((int)pnj->position.x - (int)center.x) > 1920 / 4 - 200)
        return (false);
    if (abs((int)pnj->position.y - (int)center.y) > 1080 / 4 - 100)
        return (false);
    return (true);
}
