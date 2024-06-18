/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** set_menubar_position
*/

#include "include/my_paint_header.h"

void set_button_pos(sfSprite **sprite, int x, int y)
{
    for (int i = 0; i < 3; i++) {
        sfSprite_setPosition(sprite[i], (sfVector2f){x, y});
    }
}

void set_pen_pos(l_dropmenu *pen, int y)
{
    l_dropmenu *tmp = pen;

    set_button_pos(tmp->s_button->sprites, 200, 180 + y);
    tmp = tmp->next;
    set_button_pos(tmp->s_button->sprites, 310, 265 + y);
    tmp = tmp->next;
    set_button_pos(tmp->s_button->sprites, 415, 265 + y);
}

void set_pos(sfSprite *sprite, int x, int y)
{
    sfSprite_setPosition(sprite, (sfVector2f){x, y});
}

void set_edition_pos(edition_menu *edit_menu)
{
    set_pen_pos(edit_menu->pen, 0);
    sfSprite_setPosition(edit_menu->pen_slid->back, (sfVector2f){310, 180});
    sfSprite_setPosition(edit_menu->pen_slid->dot, (sfVector2f){350, 238});
    set_pen_pos(edit_menu->eraser, 105);
    sfSprite_setPosition(edit_menu->eraser_slid->back, (sfVector2f){310, 285});
    sfSprite_setPosition(edit_menu->eraser_slid->dot, (sfVector2f){350, 343});
    set_button_pos(edit_menu->edition->sprites, 200, 10);
    set_button_pos(edit_menu->select->sprites, 200, 75);
    set_button_pos(edit_menu->fill->sprites, 200, 390);
}

void set_menubar_position(s_menubar *menubar)
{
    int y = 10;
    l_dropmenu *tmp_file = menubar->file;
    l_dropmenu *tmp_help = menubar->help;

    while (tmp_file != NULL) {
        set_button_pos(tmp_file->s_button->sprites, 10, y);
        tmp_file = tmp_file->next;
        y += 65;
    }
    y = 10;
    set_edition_pos(menubar->edition);
    while (tmp_help != NULL) {
        set_button_pos(tmp_help->s_button->sprites, 390, y);
        tmp_help = tmp_help->next;
        y += 65;
    }
    set_button_pos(menubar->redo->sprites, 1810, 10);
    set_button_pos(menubar->undo->sprites, 1690, 10);
}
