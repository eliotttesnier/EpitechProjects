/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** save
*/

#include "rpg_header.h"

void save_eny(gamedata_t *game, int fd)
{
    ennemy_t *tmp = game->entity->ennemy;

    dprintf(fd, "ENY:");
    while (tmp != NULL) {
        dprintf(fd, "%s,%i,%i,%i", tmp->path, tmp->id,
            tmp->sprite->rect.width, tmp->sprite->rect.height);
        dprintf(fd, ",%.0f,%.0f,%.0f,%.0f", tmp->position.x, tmp->position.y,
            tmp->anchor.x, tmp->anchor.y);
        dprintf(fd, ",%i,%i,%i,", tmp->hp, tmp->maxhp, tmp->atk);
        dprintf(fd, "%i;", tmp->respawn_time);
        tmp = tmp->next;
    }
    dprintf(fd, "\n");
}

void save_skill(gamedata_t *game, int fd)
{
    dprintf(fd, "SKL:\n");
    (void)game;
}

void save(gamedata_t *game)
{
    int fd = open("files/save.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR |
        S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if (fd == -1)
        exit(84);
    save_player(game, fd);
    dprintf(fd, "ADV:%i\n", game->adv);
    save_bag(game, fd);
    save_stuff(game, fd);
    save_skill(game, fd);
    save_pnj(game, fd);
    save_eny(game, fd);
    save_obj(game, fd);
    save_settings(game, fd);
    close(fd);
}
