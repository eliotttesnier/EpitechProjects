/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** save_settings
*/

#include "rpg_header.h"

void save_settings(gamedata_t *game, int fd)
{
    settings_t *set = game->settings;

    dprintf(fd, "STG:");
    dprintf(fd, "%i;%i;", set->vol_sfx, set->vol_music);
    for (int i = 0; i < 11; i++) {
        dprintf(fd, "%i%c", set->keys[i], (i == 10 ? '\n' : ';'));
    }
}
