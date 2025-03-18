/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** opened_chest
*/

#include "rpg_header.h"

bool opened_chest(gamedata_t *game, int id)
{
    chest_t *chest = get_chest_by_id(game, id);

    if (chest == NULL)
        return (false);
    return (chest->opened);
}
