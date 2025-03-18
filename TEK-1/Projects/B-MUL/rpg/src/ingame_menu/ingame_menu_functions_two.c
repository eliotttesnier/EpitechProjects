/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** dragndrop
*/

#include "rpg_header.h"

void leave_button_ingame_menu(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    gamedata->menu->gamemenu->option->state = RELEASE;
    gamedata->prescene = S_GAME;
    gamedata->scene = S_START_MENU;
}
