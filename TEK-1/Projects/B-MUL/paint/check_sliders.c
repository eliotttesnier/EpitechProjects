/*
** EPITECH PROJECT, 2024
** check_sliders
** File description:
** check_sliders.c
*/

#include "include/my_paint_header.h"

void is_on_slider(s_slider *slider, sfVector2f pix)
{
    sfVector2f pos = sfSprite_getPosition(slider->dot);
    sfFloatRect size = sfSprite_getGlobalBounds(slider->dot);

    if (pix.x > pos.x && pix.x < (pos.x + size.width) &&
        pix.y > pos.y && pix.y < (pos.y + size.height))
        slider->active = true;
}

void check_shapes(l_dropmenu *square, l_dropmenu *circle, sfVector2f pix)
{
    if (is_on_button(pix, square->s_button) == true) {
        square->s_button->state = CLICKED;
        circle->s_button->state = STATIC;
    }
    if (is_on_button(pix, circle->s_button) == true) {
        circle->s_button->state = CLICKED;
        square->s_button->state = STATIC;
    }
}

void check_sliders(edition_menu *menu, sfVector2f pix)
{
    if (menu->eraser->extended == true) {
        check_shapes(menu->eraser->next, menu->eraser->next->next, pix);
        is_on_slider(menu->eraser_slid, pix);
    }
    if (menu->pen->extended == true) {
        check_shapes(menu->pen->next, menu->pen->next->next, pix);
        is_on_slider(menu->pen_slid, pix);
    }
}
