/*
** EPITECH PROJECT, 2024
** actualise_states
** File description:
** actualise_states
*/

#include "include/my_paint_header.h"

void reset_states(edition_menu *menu)
{
    menu->fill->state = STATIC;
    menu->select->state = STATIC;
    menu->eraser->extended = false;
    menu->eraser->s_button->state = STATIC;
    menu->pen->extended = false;
    menu->pen->s_button->state = STATIC;
}

void active_state(l_dropmenu *drop)
{
    drop->extended = true;
    drop->s_button->state = CLICKED;
}

void change_active_state(edition_menu *menu)
{
    reset_states(menu);
    if (menu->tool == ERASE)
        active_state(menu->eraser);
    if (menu->tool == DRAW)
        active_state(menu->pen);
    if (menu->tool == FILL)
        menu->fill->state = CLICKED;
    if (menu->tool == SELECT)
        menu->select->state = CLICKED;
}
