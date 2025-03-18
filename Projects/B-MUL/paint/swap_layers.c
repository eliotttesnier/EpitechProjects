/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** swap_layers
*/

#include "include/my_paint_header.h"

l_image *swap_first_node(l_image *tmp, l_image *tmp_2)
{
    tmp->next = tmp_2->next;
    tmp_2->next = tmp;
    return (tmp_2);
}

void swap_two_nodes(l_image *tmp, l_image *tmp_2)
{
    tmp->next = tmp_2->next;
    tmp_2->next = tmp_2->next->next;
    tmp->next->next = tmp_2;
}

void swap_layers(s_workspace *work)
{
    l_action_queue *active = find_current(work);
    l_image *tmp = active->layer_list;

    if (tmp->layer->state == CLICKED)
        tmp->layer->state = STATIC;
    if (tmp->next->layer->state == CLICKED) {
        active->layer_list = swap_first_node(tmp, tmp->next);
        tmp->next->layer->state = STATIC;
    }
    while (tmp->next->next != NULL) {
        if (tmp->next->next->layer->state == CLICKED) {
            swap_two_nodes(tmp, tmp->next);
            tmp->next->layer->state = STATIC;
        }
        tmp = tmp->next;
    }
    set_layer_button_pos(active->layer_list);
}
