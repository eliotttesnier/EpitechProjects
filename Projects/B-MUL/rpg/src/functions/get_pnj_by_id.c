/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** get_pnj_by_id
*/

#include "rpg_header.h"

pnj_t *get_pnj_by_id(gamedata_t *game, int id)
{
    pnj_t *pnj = game->entity->pnj;

    for (; pnj != NULL; pnj = pnj->next) {
        if (pnj->id == id) {
            return pnj;
        }
    }
    return NULL;
}
