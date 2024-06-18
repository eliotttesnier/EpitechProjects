/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** save_obj
*/

#include "rpg_header.h"

void save_a_chest(chest_t *chest, int fd)
{
    dprintf(fd, "CHEST,%s,%i,%.0f,%.0f,%i,%i;", chest->path,
        chest->content->id, chest->position.x, chest->position.y,
        chest->id, (chest->opened ? 1 : 0));
}

void save_obj(gamedata_t *game, int fd)
{
    dprintf(fd, "OBJ:");
    for (chest_t *tmp = game->obj->chests; tmp != NULL; tmp = tmp->next) {
        save_a_chest(tmp, fd);
    }
    dprintf(fd, "\n");
}
