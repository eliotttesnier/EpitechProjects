/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** entity_hitbox
*/

#include "rpg_header.h"

bool is_in_pnj_hitbox(sfVector2f pos, pnj_t *pnj)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(pnj->sprite->sprite);

    rect.left += 2;
    rect.width -= 2;
    if (pos.x < rect.left || pos.x > rect.left + rect.width)
        return (false);
    rect.top += 13;
    rect.height -= 15;
    if (pos.y < rect.top || pos.y > rect.top + rect.height)
        return (false);
    return (true);
}

bool is_in_eny_hitbox(sfVector2f pos, ennemy_t *eny)
{
    sfFloatRect rect = get_eny_hitbox(eny);

    if (pos.x < rect.left || pos.x > rect.left + rect.width)
        return (false);
    if (pos.y < rect.top || pos.y > rect.top + rect.height)
        return (false);
    return (true);
}

static bool check_pnj(float x, float y, pnj_t *pnj)
{
    if (is_in_pnj_hitbox((sfVector2f){x, y + 10}, pnj))
        return (true);
    if (is_in_pnj_hitbox((sfVector2f){x + 15, y + 10}, pnj))
        return (true);
    if (is_in_pnj_hitbox((sfVector2f){x, y + 23}, pnj))
        return (true);
    if (is_in_pnj_hitbox((sfVector2f){x + 15, y + 23}, pnj))
        return (true);
    return (false);
}

static bool check_eny(float x, float y, ennemy_t *eny)
{
    if (is_in_eny_hitbox((sfVector2f){x, y + 10}, eny))
        return (true);
    if (is_in_eny_hitbox((sfVector2f){x + 15, y + 10}, eny))
        return (true);
    if (is_in_eny_hitbox((sfVector2f){x, y + 23}, eny))
        return (true);
    if (is_in_eny_hitbox((sfVector2f){x + 15, y + 23}, eny))
        return (true);
    return (false);
}

bool check_entity(gamedata_t *game, float x, float y)
{
    for (pnj_t *pnj = game->entity->pnj; pnj != NULL; pnj = pnj->next) {
        if (!is_pnj_visible(game, pnj))
            continue;
        if (check_pnj(x, y, pnj))
            return (true);
    }
    for (ennemy_t *eny = game->entity->ennemy; eny != NULL; eny = eny->next) {
        if (!eny->alive)
            continue;
        if (!is_eny_visible(game, eny))
            continue;
        if (check_eny(x, y, eny))
            return (true);
    }
    return (check_object(game, x, y));
}
