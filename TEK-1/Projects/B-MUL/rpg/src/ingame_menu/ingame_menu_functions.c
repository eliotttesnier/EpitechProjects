/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** dragndrop
*/

#include "rpg_header.h"

void save_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    save(gamedata);
    gamedata->prescene = S_PAUSE_MENU;
    gamedata->scene = S_GAME;
    put_popup(gamedata, "Game successfully saved");
}

void load_button_ingame_menu(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    load(gamedata, false);
    gamedata->prescene = S_PAUSE_MENU;
    gamedata->scene = S_GAME;
    update_view(gamedata);
    put_popup(gamedata, "Game successfully loaded");
}

void settings_button_ingame_menu(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    gamedata->menu->gamemenu->option->state = RELEASE;
    gamedata->prescene = S_PAUSE_MENU;
    gamedata->scene = S_SETTINGS_MENU;
}

void inventory_button(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    gamedata->menu->gamemenu->inventory->state = RELEASE;
    gamedata->prescene = S_PAUSE_MENU;
    gamedata->scene = S_INVENTORY;
}

void close_button_ingame_menu(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;

    gamedata->menu->gamemenu->back->state = RELEASE;
    gamedata->prescene = S_PAUSE_MENU;
    gamedata->scene = S_GAME;
}
