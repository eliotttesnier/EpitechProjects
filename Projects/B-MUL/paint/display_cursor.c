/*
** EPITECH PROJECT, 2024
** display cursor
** File description:
** display cursor
*/

#include "include/my_paint_header.h"

void set_cursor(sfSprite *sprite, sfRenderWindow *win, sfVector2f pix, int min)
{
    sfSprite_setPosition(sprite, (sfVector2f){pix.x - min, pix.y - min});
    sfRenderWindow_drawSprite(win, sprite, NULL);
}

void set_shape(edition_menu *menu, sfRenderWindow *win, l_dropmenu *drop,
    s_slider *slider)
{
    sfVector2f pix = get_pixcoord(win);
    float sq_si = slider->thickness * 1.5;
    float s_pox = pix.x - slider->thickness * 0.75;
    float s_poy = pix.y - slider->thickness * 0.75;
    float c_pox = pix.x - slider->thickness;
    float c_poy = pix.y - slider->thickness;

    if (drop->next->s_button->state == CLICKED) {
        sfCircleShape_setRadius(menu->circle, slider->thickness);
        sfCircleShape_setPosition(menu->circle, (sfVector2f){c_pox, c_poy});
        sfRenderWindow_drawCircleShape(win, menu->circle, NULL);
    }
    if (drop->next->next->s_button->state == CLICKED) {
        sfRectangleShape_setSize(menu->square, (sfVector2f){sq_si, sq_si});
        sfRectangleShape_setPosition(menu->square, (sfVector2f){s_pox, s_poy});
        sfRenderWindow_drawRectangleShape(win, menu->square, NULL);
    }
}

void display_cursor(sfRenderWindow *win, s_menubar *menubar)
{
    sfVector2f pix = get_pixcoord(win);
    sfSprite *sprite = menubar->edition->cursors[menubar->edition->tool];

    if (menubar->edition->tool == DRAW)
        set_shape(menubar->edition, win, menubar->edition->pen,
            menubar->edition->pen_slid);
    if (menubar->edition->tool == ERASE)
        set_shape(menubar->edition, win, menubar->edition->eraser,
            menubar->edition->eraser_slid);
    if (menubar->edition->tool == DRAW || menubar->edition->tool == SELECT)
        set_cursor(sprite, win, pix, 0);
    else
        set_cursor(sprite, win, pix, 5);
}
