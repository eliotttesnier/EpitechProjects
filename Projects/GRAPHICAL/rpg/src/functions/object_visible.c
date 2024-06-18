/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** object_visible
*/

#include "rpg_header.h"

bool is_chest_visible(gamedata_t *game, chest_t *chest)
{
    sfVector2f center = sfView_getCenter(game->window->view);

    if (abs((int)chest->position.x - (int)center.x) > 1920 / 4 - 150)
        return (false);
    if (abs((int)chest->position.y - (int)center.y) > 1080 / 4 - 50)
        return (false);
    return (true);
}
