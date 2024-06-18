/*
** EPITECH PROJECT, 2024
** events
** File description:
** events
*/

#include "include/my_paint_header.h"

void manage_key_pressed(sfKeyEvent e, edition_menu *menu, s_workspace *work)
{
    if (e.code == 59 && menu->tool == SELECT)
        replace_rectangle(menu, work, sfTransparent);
    if (e.code == 58 && menu->tool == SELECT)
        replace_rectangle(menu, work, work->color);
}

void manage_mouse_scroll(sfMouseWheelScrollEvent *event, sfRenderWindow *win)
{
    return;
}

void manage_mouse_release(s_menubar *menubar, s_workspace *workspace)
{
    menubar->edition->pen_slid->active = false;
    menubar->edition->eraser_slid->active = false;
    workspace->using_tool = false;
    menubar->edition->selection->active = false;
}

void analyse_events(sfRenderWindow *win, sfEvent *event, s_menubar *menubar,
    s_workspace *workspace)
{
    change_active_state(menubar->edition);
    check_hover(menubar, workspace, win);
    while (sfRenderWindow_pollEvent(win, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(win);
        if (event->type == sfEvtMouseButtonPressed)
            manage_mouse_click(win, menubar, workspace);
        if (event->type == sfEvtMouseButtonReleased)
            manage_mouse_release(menubar, workspace);
        if (event->type == sfEvtMouseWheelScrolled)
            manage_mouse_scroll(&event->mouseWheelScroll, win);
        if (event->type == sfEvtKeyPressed)
            manage_key_pressed(event->key, menubar->edition, workspace);
    }
    move_sliders(win, menubar->edition);
}
