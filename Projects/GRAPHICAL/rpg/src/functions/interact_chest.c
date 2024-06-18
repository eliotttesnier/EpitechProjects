/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** interact_chest
*/

#include "rpg_header.h"

bool is_in_chest_interact(sfVector2f pos, chest_t *chest)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(chest->sprite->sprite);

    if (pos.x < rect.left || pos.x > rect.left + rect.width)
        return (false);
    if (pos.y < rect.top || pos.y > rect.top + rect.height)
        return (false);
    return (true);
}

bool check_chest_interact(float x, float y, chest_t *chest)
{
    if (is_in_chest_interact((sfVector2f){x, y + 10}, chest))
        return (true);
    if (is_in_chest_interact((sfVector2f){x + 15, y + 10}, chest))
        return (true);
    if (is_in_chest_interact((sfVector2f){x, y + 23}, chest))
        return (true);
    if (is_in_chest_interact((sfVector2f){x + 15, y + 23}, chest))
        return (true);
    return (false);
}

chest_t *interact_chest(gamedata_t *game)
{
    sfVector2f pos = game->entity->player->position;

    for (chest_t *tmp = game->obj->chests; tmp != NULL; tmp = tmp->next) {
        if (!is_chest_visible(game, tmp))
            continue;
        if (check_chest_interact(pos.x + 2, pos.y, tmp))
            return (tmp);
        if (check_chest_interact(pos.x - 2, pos.y, tmp))
            return (tmp);
        if (check_chest_interact(pos.x, pos.y + 2, tmp))
            return (tmp);
        if (check_chest_interact(pos.x, pos.y - 2, tmp))
            return (tmp);
    }
    return (NULL);
}
