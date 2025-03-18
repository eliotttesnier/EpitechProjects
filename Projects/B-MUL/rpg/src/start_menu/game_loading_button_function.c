/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** game loading button fonction
*/

#include "rpg_header.h"

void back_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    gamedata->menu->startmenu->back->state = RELEASE;
    gamedata->menu->optionmenu->back->state = RELEASE;
    gamedata->menu->gamemenu->back->state = RELEASE;
    gamedata->scene = gamedata->prescene;
    if (gamedata->prescene == S_PAUSE_MENU) {
        update_view((gamedata));
    }
}

void newsave_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    sfMusic_stop(gamedata->music->menu);
    load(gamedata, true);
    gamedata->prescene = S_START_MENU;
    gamedata->scene = S_GAME;
    gamedata->adv = 0;
}

void load_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    adv_t adv = gamedata->adv;

    sfMusic_stop(gamedata->music->menu);
    load(gamedata, false);
    gamedata->prescene = S_START_MENU;
    gamedata->scene = S_GAME;
    gamedata->adv = adv;
}
