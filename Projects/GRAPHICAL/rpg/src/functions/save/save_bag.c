/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** save_bag
*/

#include "rpg_header.h"

void save_bag(gamedata_t *game, int fd)
{
    backpack_t *tmp = game->inventory->backpack;

    dprintf(fd, "BAG:");
    while (tmp != NULL) {
        dprintf(fd, "%i", tmp->item->id);
        if (tmp->next != NULL)
            dprintf(fd, ";");
        tmp = tmp->next;
    }
    dprintf(fd, "\n");
}
