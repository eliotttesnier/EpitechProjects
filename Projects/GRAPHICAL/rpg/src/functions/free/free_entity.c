/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_entity
*/

#include "rpg_header.h"

void free_player(player_t *player)
{
    free_animation(player->animation);
    free_movement(player->movement);
    for (int i = 0; i < 4; i++) {
        free_sprite_l(player->sprite[i]);
    }
    for (int i = 0; i < 3; i++) {
        free_sprite_l(player->attack[i]);
    }
    free(player->stat);
}

void free_enemy(ennemy_t *eny)
{
    if (eny == NULL)
        return;
    free_enemy(eny->next);
    free_animation(eny->animation);
    free_movement(eny->movement);
    free_sprite(eny->sprite);
    sfClock_destroy(eny->respawn);
    sfRectangleShape_destroy(eny->lifebar->back);
    sfRectangleShape_destroy(eny->lifebar->life);
    free(eny->lifebar);
    free(eny->path);
    free(eny);
}

void free_pnj(pnj_t *pnj)
{
    if (pnj == NULL)
        return;
    free_pnj(pnj->next);
    free_animation(pnj->animation);
    free_movement(pnj->movement);
    free_sprite(pnj->sprite);
    free(pnj->path);
    free(pnj);
}

void free_entity(entity_t *entity)
{
    free_player(entity->player);
    free_enemy(entity->ennemy);
    free_pnj(entity->pnj);
    free(entity);
}
