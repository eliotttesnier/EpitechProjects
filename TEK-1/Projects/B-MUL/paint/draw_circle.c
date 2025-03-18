/*
** EPITECH PROJECT, 2024
** draw_circle
** File description:
** draw_circle
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

void draw_square(sfImage *image, sfVector2f pix, sfColor color, int size)
{
    size = size * 1.5;
    for (int x = pix.x - (size / 2); x <= pix.x + (size / 2); x++) {
        for (int y = pix.y - (size / 2); y <= pix.y + (size / 2); y++) {
            set_pixel(image, (int)x, (int)y, color);
        }
    }
}

void draw_circle(sfImage *image, sfVector2f pix, sfColor color, int rayon)
{
    float radians = 0;
    float angle = 0;
    float x = 0;
    float y = 0;

    if (rayon == 0)
        return;
    for (angle = 0; angle <= 360; angle = angle + 0.1) {
        radians = angle * (3.14 / 180);
        x = pix.x + rayon * cos(radians);
        y = pix.y + rayon * sin(radians);
        set_pixel(image, (int)x, (int)y, color);
    }
    draw_circle(image, pix, color, rayon -1);
}
