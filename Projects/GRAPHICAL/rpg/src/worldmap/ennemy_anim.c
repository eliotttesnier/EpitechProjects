/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** ennemy_anim
*/

#include "rpg_header.h"

void eny_dir_anim(ennemy_t *eny)
{
    sfVector2f dir = eny->movement->direction;

    eny->sprite->rect.top = 0;
    if (dir.x == 0 && dir.y == 0)
        eny->sprite->rect.left = 0;
    if (dir.x == 0 && dir.y > 0)
        eny->sprite->rect.top = eny->sprite->rect.height * 0;
    if (dir.x > 0)
        eny->sprite->rect.top = eny->sprite->rect.height * 2;
    if (dir.x < 0)
        eny->sprite->rect.top = eny->sprite->rect.height * 1;
    if (dir.x == 0 && dir.y < 0)
        eny->sprite->rect.top = eny->sprite->rect.height * 3;
}

void eny_width_anim(ennemy_t *eny)
{
    float time = sfClock_getElapsedTime(eny->animation->clock).microseconds;

    if (time > 200000) {
        sfClock_restart(eny->animation->clock);
        eny->sprite->rect.left += eny->sprite->rect.width;
        if (eny->sprite->rect.left >=
            (int)sfTexture_getSize(eny->sprite->texture).x)
            eny->sprite->rect.left = 0;
    }
}

void eny_anim(gamedata_t *game)
{
    for (ennemy_t *eny = game->entity->ennemy; eny != NULL; eny = eny->next) {
        if (!eny->alive)
            continue;
        if (!is_eny_visible(game, eny))
            continue;
        eny_dir_anim(eny);
        eny_width_anim(eny);
    }
}
