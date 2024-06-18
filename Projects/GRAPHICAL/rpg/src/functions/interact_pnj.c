/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** interact_pnj
*/

#include "rpg_header.h"

bool is_in_pnj_interact(sfVector2f pos, pnj_t *pnj)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(pnj->sprite->sprite);

    if (pos.x < rect.left || pos.x > rect.left + rect.width)
        return (false);
    rect.top += 10;
    rect.height -= 12;
    if (pos.y < rect.top || pos.y > rect.top + rect.height)
        return (false);
    return (true);
}

bool check_pnj_interact(float x, float y, pnj_t *pnj)
{
    if (is_in_pnj_interact((sfVector2f){x, y + 10}, pnj))
        return (true);
    if (is_in_pnj_interact((sfVector2f){x + 15, y + 10}, pnj))
        return (true);
    if (is_in_pnj_interact((sfVector2f){x, y + 23}, pnj))
        return (true);
    if (is_in_pnj_interact((sfVector2f){x + 15, y + 23}, pnj))
        return (true);
    return (false);
}

pnj_t *interact_pnj(gamedata_t *game)
{
    sfVector2f pos = game->entity->player->position;

    for (pnj_t *pnj = game->entity->pnj; pnj != NULL; pnj = pnj->next) {
        if (!is_pnj_visible(game, pnj))
            continue;
        if (check_pnj_interact(pos.x + 2, pos.y, pnj))
            return (pnj);
        if (check_pnj_interact(pos.x - 2, pos.y, pnj))
            return (pnj);
        if (check_pnj_interact(pos.x, pos.y + 2, pnj))
            return (pnj);
        if (check_pnj_interact(pos.x, pos.y - 2, pnj))
            return (pnj);
    }
    return (NULL);
}
