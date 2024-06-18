/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** is_mob_killed
*/

#include "rpg_header.h"

ennemy_t *get_eny_by_id(gamedata_t *game, int id)
{
    ennemy_t *mob = game->entity->ennemy;

    for (; mob != NULL; mob = mob->next) {
        if (mob->id == id)
            return (mob);
    }
    return (NULL);
}

bool is_eny_killed(gamedata_t *game, int id)
{
    if (get_eny_by_id(game, id) == NULL)
        return (false);
    return (!get_eny_by_id(game, id)->alive);
}
