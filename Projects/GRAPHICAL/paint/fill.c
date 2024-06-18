/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** fill
*/

#include "include/my_paint_header.h"

void fill_down_left(l_image *image, sfColor color, int x, int y)
{
    sfColor pixel_c;

    if (x < 0 || x > 1380 || y < 0 || y > 570)
        return;
    pixel_c = sfImage_getPixel(image->image, x, y);
    if (pixel_c.a == sfTransparent.a &&
        pixel_c.r == sfTransparent.r &&
        pixel_c.g == sfTransparent.g &&
        pixel_c.b == sfTransparent.b) {
        sfImage_setPixel(image->image, x, y, color);
    } else
        return;
    fill_down_left(image, color, x - 1, y);
    fill_down_left(image, color, x, y + 1);
}

void fill_down_right(l_image *image, sfColor color, int x, int y)
{
    sfColor pixel_c;

    if (x < 0 || x > 1380 || y < 0 || y > 570)
        return;
    pixel_c = sfImage_getPixel(image->image, x, y);
    if (pixel_c.a == sfTransparent.a &&
        pixel_c.r == sfTransparent.r &&
        pixel_c.g == sfTransparent.g &&
        pixel_c.b == sfTransparent.b) {
        sfImage_setPixel(image->image, x, y, color);
    } else
        return;
    fill_down_right(image, color, x + 1, y);
    fill_down_right(image, color, x, y + 1);
}

void fill_up_left(l_image *image, sfColor color, int x, int y)
{
    sfColor pixel_c;

    if (x < 0 || x > 1380 || y < 0 || y > 570)
        return;
    pixel_c = sfImage_getPixel(image->image, x, y);
    if (pixel_c.a == sfTransparent.a &&
        pixel_c.r == sfTransparent.r &&
        pixel_c.g == sfTransparent.g &&
        pixel_c.b == sfTransparent.b) {
        sfImage_setPixel(image->image, x, y, color);
    } else
        return;
    fill_up_left(image, color, x - 1, y);
    fill_up_left(image, color, x, y - 1);
}

void fill_up_right(l_image *image, sfColor color, int x, int y)
{
    sfColor pixel_c;

    if (x < 0 || x > 1380 || y < 0 || y > 570)
        return;
    pixel_c = sfImage_getPixel(image->image, x, y);
    if (pixel_c.a == sfTransparent.a &&
        pixel_c.r == sfTransparent.r &&
        pixel_c.g == sfTransparent.g &&
        pixel_c.b == sfTransparent.b) {
        sfImage_setPixel(image->image, x, y, color);
    } else
        return;
    fill_up_right(image, color, x + 1, y);
    fill_up_right(image, color, x, y - 1);
}

void fill_tool(l_image *image, sfColor color, int x, int y)
{
    fill_down_left(image, color, x, y);
    fill_down_right(image, color, x + 1, y);
    fill_up_left(image, color, x, y - 1);
    fill_up_right(image, color, x + 1, y - 1);
}
