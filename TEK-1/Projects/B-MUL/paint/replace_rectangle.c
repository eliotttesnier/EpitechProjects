/*
** EPITECH PROJECT, 2024
** replace_rectangle.c
** File description:
** replace rectangle
*/

#include "include/my_paint_header.h"

static void set_pixel(sfImage *image, int x, int y, sfColor color)
{
    if (x < 0 || x > 1380)
        return;
    if (y < 0 || y > 570)
        return;
    sfImage_setPixel(image, (int)x, (int)y, color);
}

void replace_rectangle(edition_menu *men, s_workspace *work, sfColor color)
{
    l_action_queue *cur = find_current(work);
    sfFloatRect rect = sfRectangleShape_getGlobalBounds(men->selection->shape);

    for (int x = rect.left; x < rect.left + rect.width; x++) {
        for (int y = rect.top; y < rect.top + rect.height; y++) {
            set_pixel(cur->layer_list->image, x - 485, y - 285, color);
        }
    }
}
