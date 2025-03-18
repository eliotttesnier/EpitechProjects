/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** set_workspace
*/

#include "include/my_paint_header.h"

void set_colors_pos(s_button **colors)
{
    set_button_pos(colors[0]->sprites, 590, 20);
    set_button_pos(colors[1]->sprites, 590, 75);
    set_button_pos(colors[2]->sprites, 645, 20);
    set_button_pos(colors[3]->sprites, 700, 20);
    set_button_pos(colors[4]->sprites, 755, 20);
    set_button_pos(colors[5]->sprites, 645, 75);
    set_button_pos(colors[6]->sprites, 700, 75);
    set_button_pos(colors[7]->sprites, 755, 75);
}

void set_layer_pos(l_image *layer_list)
{
    l_image *tmp = layer_list;

    while (tmp != NULL) {
        set_pos(tmp->image_sprite, 485, 285);
        tmp = tmp->next;
    }
}

void set_layer_button_pos(l_image *layer_list)
{
    l_image *tmp = layer_list;

    set_button_pos(tmp->layer->sprites, 45, 300);
    tmp = tmp->next;
    set_button_pos(tmp->layer->sprites, 45, 415);
    tmp = tmp->next;
    set_button_pos(tmp->layer->sprites, 45, 530);
    tmp = tmp->next;
    set_button_pos(tmp->layer->sprites, 45, 645);
    tmp = tmp->next;
    set_button_pos(tmp->layer->sprites, 45, 760);
}

void set_workspace_position(s_workspace *workspace)
{
    set_pos(workspace->color_palette->palette, 580, 10);
    set_pos(workspace->layer_board, 10, 220);
    set_pos(workspace->work_board, 430, 220);
    set_layer_pos(workspace->action_queue->layer_list);
    set_layer_button_pos(workspace->action_queue->layer_list);
    set_colors_pos(workspace->color_palette->colors);
}
