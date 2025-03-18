/*
** EPITECH PROJECT, 2024
** check_canva
** File description:
** check_canva
*/

#include "include/my_paint_header.h"

void check_canva(s_workspace *work, sfVector2f pix)
{
    sfSprite *sprite = work->action_queue->layer_list->image_sprite;
    sfVector2f pos = sfSprite_getPosition(sprite);
    sfFloatRect size = sfSprite_getGlobalBounds(sprite);

    if (pix.x > pos.x && pix.x < (pos.x + size.width) &&
        pix.y > pos.y && pix.y < (pos.y + size.height))
        work->using_tool = true;
}
