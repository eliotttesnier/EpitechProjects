/*
** EPITECH PROJECT, 2024
** mouse_event
** File description:
** mouse_event
*/

#include "include/my_paint_header.h"

static void check_layers_click(l_image *layer_list, sfVector2f pix)
{
    l_image *tmp = layer_list;

    while (tmp != NULL) {
        if (is_on_button(pix, tmp->layer)) {
            tmp->layer->state = CLICKED;
        } else
            tmp->layer->state = STATIC;
        tmp = tmp->next;
    }
}

static bool is_on_colors(s_button **colors, sfVector2f pix)
{
    for (int i = 0; i < 8; i++) {
        if (is_on_button(pix, colors[i]))
            return (true);
    }
    return (false);
}

sfColor get_color(int i)
{
    if (i == 0)
        return (sfWhite);
    if (i == 1)
        return (sfBlack);
    if (i == 2)
        return (sfRed);
    if (i == 3)
        return (sfBlue);
    if (i == 4)
        return (sfGreen);
    if (i == 5)
        return (sfCyan);
    if (i == 6)
        return (sfMagenta);
    if (i == 7)
        return (sfYellow);
    return sfWhite;
}

void check_colors_click(s_button **colors, sfVector2f pix, s_workspace *work)
{
    if (is_on_colors(colors, pix) == false)
        return;
    for (int i = 0; i < 8; i++) {
        if (is_on_button(pix, colors[i])) {
            colors[i]->state = CLICKED;
            work->color = get_color(i);
        } else {
            colors[i]->state = STATIC;
        }
    }
}

void remove_extended_drop(l_dropmenu *menu)
{
    l_dropmenu *temp = menu->next;

    menu->extended = false;
    menu->s_button->state = STATIC;
    while (temp != NULL) {
        temp->s_button->state = STATIC;
        temp = temp->next;
    }
}

static void check_menu_buttons(l_dropmenu *menu, sfVector2f pixcoord)
{
    l_dropmenu *temp = menu->next;

    while (temp != NULL) {
        if (is_on_button(pixcoord, temp->s_button)) {
            temp->s_button->state = CLICKED;
        }
        temp = temp->next;
    }
}

static void check_drop_menu(l_dropmenu *menu, sfVector2f pixcoord,
    l_dropmenu *other, edition_menu *oth)
{
    if (is_on_button(pixcoord, menu->s_button)) {
        if (menu->s_button->state != CLICKED)
            menu->s_button->state = CLICKED;
        else
            menu->s_button->state = HOVER;
        menu->extended = !menu->extended;
        remove_extended_drop(other);
        oth->extended = false;
        oth->edition->state = STATIC;
    }
    if (menu->extended == true)
        check_menu_buttons(menu, pixcoord);
}

static void check_edit_menu(edition_menu *menu, sfVector2f pixcoord,
    l_dropmenu *other, l_dropmenu *oth)
{
    if (is_on_button(pixcoord, menu->edition)) {
        if (menu->edition->state != CLICKED)
            menu->edition->state = CLICKED;
        else
            menu->edition->state = HOVER;
        menu->extended = !menu->extended;
        remove_extended_drop(other);
        remove_extended_drop(oth);
    }
    if (is_on_button(pixcoord, menu->select) && menu->extended)
        menu->tool = SELECT;
    if (is_on_button(pixcoord, menu->fill) && menu->extended)
        menu->tool = FILL;
    if (is_on_button(pixcoord, menu->eraser->s_button) && menu->extended)
        menu->tool = ERASE;
    if (is_on_button(pixcoord, menu->pen->s_button) && menu->extended)
        menu->tool = DRAW;
    if (menu->extended == true)
        check_sliders(menu, pixcoord);
}

void click_undo_redo(s_menubar *menubar, sfVector2f pix)
{
    if (is_on_button(pix, menubar->redo) == true) {
        menubar->redo->state = CLICKED;
        menubar->undo->state = STATIC;
    }
    if (is_on_button(pix, menubar->undo) == true) {
        menubar->undo->state = CLICKED;
        menubar->redo->state = STATIC;
    }
}

void manage_mouse_click(sfRenderWindow *win,
    s_menubar *menubar, s_workspace *workspace)
{
    l_action_queue *tmp = workspace->action_queue;
    l_dropmenu *file = menubar->file;
    l_dropmenu *help = menubar->help;
    edition_menu *edit = menubar->edition;
    sfVector2f pixcoord = get_pixcoord(win);

    check_drop_menu(file, pixcoord, help, edit);
    check_drop_menu(help, pixcoord, file, edit);
    check_edit_menu(edit, pixcoord, file, help);
    click_undo_redo(menubar, pixcoord);
    check_colors_click(workspace->color_palette->colors, pixcoord, workspace);
    while (tmp != NULL && file->extended == false && edit->extended == false) {
        check_layers_click(tmp->layer_list, pixcoord);
        tmp = tmp->next;
    }
    check_canva(workspace, pixcoord);
}
