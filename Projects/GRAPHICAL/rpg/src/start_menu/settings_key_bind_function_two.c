/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** settings key bind
*/

#include "rpg_header.h"

void interact_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->interact;
    keybind->key_type = 4;
    key_bind_loop(keybind);
    free(keybind);
}

void attack_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->attack;
    keybind->key_type = 5;
    key_bind_loop(keybind);
    free(keybind);
}

void fire_spell_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->fire_spell;
    keybind->key_type = 8;
    key_bind_loop(keybind);
    free(keybind);
}

void heal_spell_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->heal_spell;
    keybind->key_type = 9;
    key_bind_loop(keybind);
    free(keybind);
}

void stun_spell_key(void *arg)
{
    gamedata_t *gamedata = (gamedata_t *)arg;
    call_key_bind_t *keybind = malloc(sizeof(call_key_bind_t));

    keybind->game = gamedata;
    keybind->keybind = gamedata->menu->optionmenu->stun_spell;
    keybind->key_type = 10;
    key_bind_loop(keybind);
    free(keybind);
}
