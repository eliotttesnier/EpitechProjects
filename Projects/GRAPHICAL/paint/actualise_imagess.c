/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** actualise_imagess
*/

#include "include/my_paint_header.h"

void actualise_image(s_workspace *work)
{
    l_action_queue *tmp = work->action_queue;
    l_image *tmp_2;

    while (tmp != NULL) {
        if (tmp->activated_state == true)
            break;
        tmp = tmp->next;
    }
    tmp_2 = tmp->layer_list;
    while (tmp_2 != NULL) {
        sfTexture_updateFromImage(tmp_2->texture, tmp_2->image, 0, 0);
        sfSprite_setTexture(tmp_2->image_sprite, tmp_2->texture, sfFalse);
        tmp_2 = tmp_2->next;
    }
}
