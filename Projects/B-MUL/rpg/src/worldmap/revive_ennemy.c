/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** revive_ennemy
*/

#include "rpg_header.h"

void check_respawn_clock(ennemy_t *tmp)
{
    if (sfClock_getElapsedTime(tmp->respawn).microseconds / 1000000 >=
        tmp->respawn_time) {
        tmp->alive = true;
        tmp->position = tmp->anchor;
        tmp->hp = tmp->maxhp;
        sfClock_restart(tmp->respawn);
        sfSprite_setPosition(tmp->sprite->sprite, tmp->position);
    }
}

void revive_ennemy(gamedata_t *game)
{
    ennemy_t *tmp = game->entity->ennemy;

    for (; tmp != NULL; tmp = tmp->next) {
        if (!tmp->alive)
            check_respawn_clock(tmp);
    }
}
