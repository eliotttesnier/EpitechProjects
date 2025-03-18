/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** ennemy_visible
*/

#include "rpg_header.h"

bool is_eny_visible(gamedata_t *game, ennemy_t *eny)
{
    sfVector2f center = sfView_getCenter(game->window->view);

    if (!eny->alive)
        return (false);
    if (abs((int)eny->position.x - (int)center.x) > 1920 / 4)
        return (false);
    if (abs((int)eny->position.y - (int)center.y) > 1080 / 4)
        return (false);
    return (true);
}
