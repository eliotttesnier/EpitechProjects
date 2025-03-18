/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** del_pnj
*/

#include "rpg_header.h"

void del_pnj(gamedata_t *game, int id)
{
    pnj_t *pnj = game->entity->pnj;
    pnj_t *tmp = NULL;

    if (pnj->id == id) {
        tmp = pnj->next;
        free(pnj);
        game->entity->pnj = tmp;
        return;
    }
    for (; pnj->next; pnj = pnj->next) {
        if (pnj->next->id == id) {
            tmp = pnj->next->next;
            free(pnj->next);
            pnj->next = tmp;
            return;
        }
    }
}
