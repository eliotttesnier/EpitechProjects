/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** settings key bind
*/

#include "rpg_header.h"

void forward_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->forward;
    keybind->key_type = 0;
    key_bind_loop(keybind);
    free(keybind);
}

void backward_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->backward;
    keybind->key_type = 1;
    key_bind_loop(keybind);
    free(keybind);
}

void left_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->left;
    keybind->key_type = 2;
    key_bind_loop(keybind);
    free(keybind);
}

void right_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->right;
    keybind->key_type = 3;
    key_bind_loop(keybind);
    free(keybind);
}

void inventory_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->inventory;
    keybind->key_type = 6;
    key_bind_loop(keybind);
    free(keybind);
}
