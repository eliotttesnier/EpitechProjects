/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** display_menu_bar
*/

#include "include/my_paint_header.h"

void display_button(sfRenderWindow *win, sfSprite **button, button_state state)
{
    sfRenderWindow_drawSprite(win, button[state], NULL);
}

void display_list(sfRenderWindow *win, l_dropmenu *menu)
{
    l_dropmenu *temp = menu;

    while (temp != NULL) {
        display_button(win, temp->s_button->sprites, temp->s_button->state);
        temp = temp->next;
    }
}

void display_edit(sfRenderWindow *win, edition_menu *edit)
{
    l_dropmenu *erase = edit->eraser;
    l_dropmenu *pen = edit->pen;
    s_button *select = edit->select;
    s_button *fill = edit->fill;

    display_button(win, erase->s_button->sprites, erase->s_button->state);
    if (erase->extended == true) {
        display_list(win, erase->next);
        sfRenderWindow_drawSprite(win, edit->eraser_slid->back, NULL);
        sfRenderWindow_drawSprite(win, edit->eraser_slid->dot, NULL);
    }
    display_button(win, pen->s_button->sprites, pen->s_button->state);
    if (pen->extended) {
        display_list(win, pen->next);
        sfRenderWindow_drawSprite(win, edit->pen_slid->back, NULL);
        sfRenderWindow_drawSprite(win, edit->pen_slid->dot, NULL);
    }
    display_button(win, select->sprites, select->state);
    display_button(win, fill->sprites, fill->state);
}

void display_menu_bar(sfRenderWindow *win, s_menubar *menubar)
{
    l_dropmenu *file = menubar->file;
    l_dropmenu *help = menubar->help;
    edition_menu *edit = menubar->edition;

    display_button(win, file->s_button->sprites, file->s_button->state);
    if (file->extended == true)
        display_list(win, file->next);
    display_button(win, help->s_button->sprites, help->s_button->state);
    if (help->extended == true)
        display_list(win, help->next);
    display_button(win, edit->edition->sprites, edit->edition->state);
    if (edit->extended == true)
        display_edit(win, edit);
    display_button(win, menubar->redo->sprites, menubar->redo->state);
    display_button(win, menubar->undo->sprites, menubar->undo->state);
}
