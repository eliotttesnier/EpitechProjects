/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** talked_to
*/

#include "rpg_header.h"

bool talked_to_pnj(gamedata_t *game, int id)
{
    pnj_t *pnj = get_pnj_by_id(game, id);

    if (pnj == NULL)
        return (false);
    return (pnj->talked);
}
