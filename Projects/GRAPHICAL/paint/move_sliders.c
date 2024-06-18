/*
** EPITECH PROJECT, 2024
** move sliders
** File description:
** move sliders
*/

#include "include/my_paint_header.h"

void move_the_slider(sfSprite *dot, sfSprite *back, sfVector2f pix)
{
    sfVector2f back_pos = sfSprite_getPosition(back);
    sfVector2f pos = sfSprite_getPosition(dot);

    if (pix.x > back_pos.x + 13 && pix.x < back_pos.x + 177)
        sfSprite_setPosition(dot, (sfVector2f){pix.x, pos.y});
    if (pix.x < back_pos.x + 13)
        sfSprite_setPosition(dot, (sfVector2f){back_pos.x + 13, pos.y});
    if (pix.x > back_pos.x + 177)
        sfSprite_setPosition(dot, (sfVector2f){back_pos.x + 177, pos.y});
}

void actualise_thickness(s_slider *slider)
{
    int x = (int)sfSprite_getPosition(slider->dot).x;

    slider->thickness = x - 318;
}

void move_sliders(sfRenderWindow *win, edition_menu *menu)
{
    sfVector2f pix = get_pixcoord(win);

    if (menu->eraser_slid->active == true)
        move_the_slider(menu->eraser_slid->dot, menu->eraser_slid->back, pix);
    if (menu->pen_slid->active == true)
        move_the_slider(menu->pen_slid->dot, menu->pen_slid->back, pix);
    actualise_thickness(menu->eraser_slid);
    actualise_thickness(menu->pen_slid);
}
