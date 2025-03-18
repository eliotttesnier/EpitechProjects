/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** pnj_anim
*/

#include "rpg_header.h"

void get_dir_rect_pnj(pnj_t *pnj)
{
    sfVector2f dir = pnj->movement->direction;

    pnj->sprite->rect.top = 0;
    if (dir.x == 0 && dir.y == 0)
        pnj->sprite->rect.left = 0;
    if (dir.x == 0 && dir.y > 0)
        pnj->sprite->rect.top = pnj->sprite->rect.height * 0;
    if (dir.x > 0)
        pnj->sprite->rect.top = pnj->sprite->rect.height * 2;
    if (dir.x < 0)
        pnj->sprite->rect.top = pnj->sprite->rect.height * 1;
    if (dir.x == 0 && dir.y < 0)
        pnj->sprite->rect.top = pnj->sprite->rect.height * 3;
}

void anim_single_pnj(pnj_t *pnj)
{
    float time = sfClock_getElapsedTime(pnj->animation->clock).microseconds;

    if (time > 200000) {
        sfClock_restart(pnj->animation->clock);
        pnj->sprite->rect.left += pnj->sprite->rect.width;
        if (pnj->sprite->rect.left == pnj->sprite->rect.width * 4)
            pnj->sprite->rect.left = 0;
    }
    get_dir_rect_pnj(pnj);
}

void pnj_anim(gamedata_t *game)
{
    pnj_t *tmp = game->entity->pnj;

    while (tmp != NULL) {
        if (is_pnj_visible(game, tmp))
            anim_single_pnj(tmp);
        tmp = tmp->next;
    }
}
