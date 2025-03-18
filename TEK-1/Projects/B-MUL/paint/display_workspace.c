/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** display_workspace
*/

#include "include/my_paint_header.h"

static void displays_in_order(sfRenderWindow *win, l_image *img)
{
    if (img == NULL)
        return;
    displays_in_order(win, img->next);
    sfRenderWindow_drawSprite(win, img->image_sprite, NULL);
}

void display_layers(sfRenderWindow *win, s_workspace *work)
{
    l_action_queue *tmp = work->action_queue;

    while (tmp != NULL) {
        if (tmp->activated_state == true)
            break;
        tmp = tmp->next;
    }
    displays_in_order(win, tmp->layer_list);
}

void display_colors(sfRenderWindow *win, s_button **colors)
{
    display_button(win, colors[0]->sprites, colors[0]->state);
    display_button(win, colors[1]->sprites, colors[1]->state);
    display_button(win, colors[2]->sprites, colors[2]->state);
    display_button(win, colors[3]->sprites, colors[3]->state);
    display_button(win, colors[4]->sprites, colors[4]->state);
    display_button(win, colors[5]->sprites, colors[5]->state);
    display_button(win, colors[6]->sprites, colors[6]->state);
    display_button(win, colors[7]->sprites, colors[7]->state);
}

void display_layer_button(sfRenderWindow *win, l_image *layer_list)
{
    l_image *tmp = layer_list;

    display_button(win, tmp->layer->sprites, tmp->layer->state);
    tmp = tmp->next;
    display_button(win, tmp->layer->sprites, tmp->layer->state);
    tmp = tmp->next;
    display_button(win, tmp->layer->sprites, tmp->layer->state);
    tmp = tmp->next;
    display_button(win, tmp->layer->sprites, tmp->layer->state);
    tmp = tmp->next;
    display_button(win, tmp->layer->sprites, tmp->layer->state);
}

void display_workspace(sfRenderWindow *win, s_workspace *workspace)
{
    l_action_queue *tmp = workspace->action_queue;

    sfRenderWindow_drawSprite(win, workspace->color_palette->palette, NULL);
    display_colors(win, workspace->color_palette->colors);
    sfRenderWindow_drawSprite(win, workspace->layer_board, NULL);
    sfRenderWindow_drawSprite(win, workspace->work_board, NULL);
    display_layers(win, workspace);
    while (tmp != NULL) {
        display_layer_button(win, tmp->layer_list);
        tmp = tmp->next;
    }
}
