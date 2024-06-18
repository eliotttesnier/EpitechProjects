/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** save_pnj
*/

#include "rpg_header.h"

void save_voicebox(voicebox_t *voice, int fd)
{
    voicebox_t *stop;
    voicebox_t *tmp;

    for (stop = voice; stop->next != voice; stop = stop->next);
    for (tmp = voice; tmp != NULL; tmp = tmp->next) {
        dprintf(fd, ",%s", tmp->msg);
        if (tmp == stop)
            break;
    }
}

void save_pnj(gamedata_t *game, int fd)
{
    pnj_t *tmp = game->entity->pnj;
    voicebox_t *voice;

    dprintf(fd, "PNJ:");
    while (tmp != NULL) {
        dprintf(fd, "%s,%i,%.0f,%.0f,%.0f,%.0f", tmp->path, tmp->id,
            tmp->position.x, tmp->position.y, tmp->anchor.x, tmp->anchor.y);
        voice = tmp->voicebox;
        if (voice != NULL)
            save_voicebox(voice, fd);
        dprintf(fd, ";");
        tmp = tmp->next;
    }
    dprintf(fd, "\n");
}
