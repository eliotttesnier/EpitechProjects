/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_menu
*/

#include "rpg_header.h"

void free_creditmenu(credit_menu_t *creditmenu)
{
    sfClock_destroy(creditmenu->clock);
    free_sprite(creditmenu->back);
    free_sprite(creditmenu->display);
    free_button(creditmenu->backbutt);
    free(creditmenu);
}

void free_gamemenu(gamemenu_t *menu)
{
    free_sprite(menu->panel);
    free_button(menu->back);
    free_button(menu->close);
    free_button(menu->inventory);
    free_button(menu->load);
    free_button(menu->option);
    free_button(menu->quit);
    free_button(menu->save);
    free(menu);
}

void free_startmenu(startmenu_t *menu)
{
    free_button(menu->back);
    free_button(menu->credits);
    free_sprite(menu->background);
    free_button(menu->leave);
    free_button(menu->load);
    free_button(menu->newsave);
    free_button(menu->play);
    free_button(menu->settings);
    free_sprite(menu->first_panel);
    free_sprite(menu->second_panel);
    free_text(menu->titre);
    free(menu);
}

void free_menu(menu_t *menu)
{
    free_creditmenu(menu->creditmenu);
    free_gamemenu(menu->gamemenu);
    free_startmenu(menu->startmenu);
}
