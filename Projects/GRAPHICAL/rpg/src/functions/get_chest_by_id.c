/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** get_chest_by_id
*/

#include "rpg_header.h"

chest_t *get_chest_by_id(gamedata_t *game, int id)
{
    chest_t *tmp = game->obj->chests;

    while (tmp != NULL) {
        if (tmp->id == id)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}
