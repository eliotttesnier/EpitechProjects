/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** start menu button function
*/

#include "rpg_header.h"

void play_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    gamedata->menu->startmenu->play->state = RELEASE;
    gamedata->prescene = S_START_MENU;
    gamedata->scene = S_GAME_LOADING;
}

void leave_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    sfRenderWindow_close(gamedata->window->window);
}

void credit_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    gamedata->scene = S_CREDITS_MENU;
}

void settings_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    gamedata->menu->startmenu->settings->state = RELEASE;
    gamedata->prescene = S_START_MENU;
    gamedata->scene = S_SETTINGS_MENU;
}
