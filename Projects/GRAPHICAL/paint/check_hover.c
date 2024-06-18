/*
** EPITECH PROJECT, 2024
** check_hover
** File description:
** check if is hover
*/

#include "include/my_paint_header.h"

void check_button(s_button *button, sfVector2f pixcoord)
{
    if (button->state == CLICKED)
        return;
    if (is_on_button(pixcoord, button))
        button->state = HOVER;
    else
        button->state = STATIC;
}

void check_layers(l_action_queue *queue, sfVector2f pix)
{
    l_action_queue *tmp = queue;
    l_image *tmp2;

    while (tmp != NULL && tmp->activated_state != true) {
        tmp = tmp->next;
    }
    tmp2 = tmp->layer_list;
    while (tmp2 != NULL) {
        check_button(tmp2->layer, pix);
        tmp2 = tmp2->next;
    }
}

void check_colors(s_button **button, sfVector2f pix)
{
    for (int i = 0; i < 8; i++) {
        check_button(button[i], pix);
    }
}

static void check_all_list(l_dropmenu *menu, sfVector2f pixcoord)
{
    l_dropmenu *temp = menu;

    while (temp != NULL) {
        check_button(temp->s_button, pixcoord);
        temp = temp->next;
    }
}

static void check_drop_menu(l_dropmenu *menu, sfVector2f pixcoord)
{
    if (menu->s_button->state == CLICKED) {
        check_all_list(menu->next, pixcoord);
        return;
    }
    check_button(menu->s_button, pixcoord);
}

static void check_all_edit(edition_menu *edit, sfVector2f pixcoord)
{
    l_dropmenu *eraser = edit->eraser;
    l_dropmenu *pen = edit->pen;
    s_button *select = edit->select;
    s_button *fill = edit->fill;

    check_drop_menu(eraser, pixcoord);
    check_drop_menu(pen, pixcoord);
    check_button(select, pixcoord);
    check_button(fill, pixcoord);
}

static void check_edit_menu(edition_menu *menu, sfVector2f pixcoord)
{
    if (menu->edition->state == CLICKED) {
        check_all_edit(menu, pixcoord);
        return;
    }
    if (is_on_button(pixcoord, menu->edition))
        menu->edition->state = HOVER;
    else
        menu->edition->state = STATIC;
}

void check_undo_redo(s_menubar *menubar, sfVector2f pix)
{
    check_button(menubar->redo, pix);
    check_button(menubar->undo, pix);
}

void check_hover(s_menubar *menubar, s_workspace *workspace,
    sfRenderWindow *win)
{
    l_dropmenu *file = menubar->file;
    l_dropmenu *help = menubar->help;
    edition_menu *edit = menubar->edition;
    sfVector2f pixcoord = get_pixcoord(win);

    check_drop_menu(file, pixcoord);
    check_drop_menu(help, pixcoord);
    check_edit_menu(edit, pixcoord);
    check_undo_redo(menubar, pixcoord);
    check_colors(workspace->color_palette->colors, pixcoord);
    if (file->extended == false && edit->extended == false)
        check_layers(workspace->action_queue, pixcoord);
}
