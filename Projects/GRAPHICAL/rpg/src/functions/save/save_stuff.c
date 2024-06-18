/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** save_stuff
*/

#include "rpg_header.h"

void save_stuff(gamedata_t *game, int fd)
{
    if (game->inventory->equipment->equiped[0] == NULL)
        dprintf(fd, "STF:84;");
    else
        dprintf(fd, "STF:%i,", game->inventory->equipment->equiped[0]->id);
    if (game->inventory->equipment->equiped[1] == NULL)
        dprintf(fd, "84;");
    else
        dprintf(fd, "%i,", game->inventory->equipment->equiped[1]->id);
    if (game->inventory->equipment->equiped[2] == NULL)
        dprintf(fd, "84;");
    else
        dprintf(fd, "%i,", game->inventory->equipment->equiped[2]->id);
    if (game->inventory->equipment->equiped[3] == NULL)
        dprintf(fd, "84;");
    else
        dprintf(fd, "%i,", game->inventory->equipment->equiped[3]->id);
    if (game->inventory->equipment->equiped[4] == NULL)
        dprintf(fd, "84\n");
    else
        dprintf(fd, "%i\n", game->inventory->equipment->equiped[4]->id);
}
