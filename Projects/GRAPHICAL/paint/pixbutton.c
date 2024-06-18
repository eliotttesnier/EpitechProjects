/*
** EPITECH PROJECT, 2024
** pixbutton
** File description:
** pixcoord and is_on_button
*/

#include "include/my_paint_header.h"

bool is_on_button(sfVector2f pixcoord, s_button *button)
{
    sfVector2f pos = sfSprite_getPosition(button->sprites[0]);
    sfFloatRect size = sfSprite_getGlobalBounds(button->sprites[0]);

    if (pixcoord.x > pos.x && pixcoord.x < (pos.x + size.width) &&
        pixcoord.y > pos.y && pixcoord.y < (pos.y + size.height))
        return (true);
    return (false);
}

sfVector2f get_pixcoord(sfRenderWindow *win)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win);
    sfView *view = sfRenderWindow_getView(win);
    sfVector2f pixcoord = sfRenderWindow_mapPixelToCoords(win, mouse, view);

    return (pixcoord);
}
