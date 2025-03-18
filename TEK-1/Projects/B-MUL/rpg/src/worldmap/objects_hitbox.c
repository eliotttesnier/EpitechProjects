/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** objects_hitbox
*/

#include "rpg_header.h"

bool is_in_chest_hitbox(sfVector2f pos, chest_t *tmp)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(tmp->sprite->sprite);

    rect.left += 2;
    rect.width -= 4;
    if (pos.x < rect.left || pos.x > rect.left + rect.width)
        return (false);
    rect.top += 13;
    rect.height -= 15;
    if (pos.y < rect.top || pos.y > rect.top + rect.height)
        return (false);
    return (true);
}

bool check_chest(float x, float y, chest_t *chest)
{
    if (is_in_chest_hitbox((sfVector2f){x, y + 10}, chest))
        return (true);
    if (is_in_chest_hitbox((sfVector2f){x + 15, y + 10}, chest))
        return (true);
    if (is_in_chest_hitbox((sfVector2f){x, y + 23}, chest))
        return (true);
    if (is_in_chest_hitbox((sfVector2f){x + 15, y + 23}, chest))
        return (true);
    return (false);
}

bool check_object(gamedata_t *game, float x, float y)
{
    for (chest_t *tmp = game->obj->chests; tmp != NULL; tmp = tmp->next) {
        if (!is_chest_visible(game, tmp))
            continue;
        if (check_chest(x, y, tmp))
            return (true);
    }
    return (false);
}
