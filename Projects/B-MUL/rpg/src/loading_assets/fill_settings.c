/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** fill_settings
*/

#include "rpg_header.h"

void fill_settings(gamedata_t *gamedata, config_t *config)
{
    config_t *tmp = config;

    gamedata->settings = malloc(sizeof(settings_t));
    while (tmp != NULL) {
        if (strcmp(tmp->line[0], "STG") == 0)
            break;
        tmp = tmp->next;
    }
    gamedata->settings->vol_music = atoi(tmp->line[1]);
    gamedata->settings->vol_sfx = atoi(tmp->line[2]);
    gamedata->settings->keys = malloc(sizeof(sfKeyCode) * 11);
    for (int i = 0; i < 11; i++) {
        gamedata->settings->keys[i] = atoi(tmp->line[i + 3]);
    }
}
