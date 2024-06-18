/*
** EPITECH PROJECT, 2024
** destroy_paint
** File description:
** destroy_paint
*/

#include "include/my_paint_header.h"

void free_button(s_button *button)
{
    for (int i = 0; i < 3; i++) {
        sfSprite_destroy(button->sprites[i]);
        sfTexture_destroy(button->textures[i]);
    }
    free(button);
}

void free_dropmenu(l_dropmenu *menu)
{
    l_dropmenu *temp = menu;

    if (temp == NULL)
        return;
    free_dropmenu(temp->next);
    free_button(temp->s_button);
    free(menu);
}

static void free_selection(s_selection *select, edition_menu *menu)
{
    sfCircleShape_destroy(menu->circle);
    sfRectangleShape_destroy(menu->square);
    sfRectangleShape_destroy(select->shape);
    free(select);
}

void free_edition(edition_menu *menu)
{
    free_dropmenu(menu->eraser);
    free_dropmenu(menu->pen);
    free_button(menu->edition);
    free_button(menu->fill);
    free_button(menu->select);
    for (int i = 0; i < 4; i++) {
        sfSprite_destroy(menu->cursors[i]);
        sfTexture_destroy(menu->cu_textu[i]);
    }
    sfTexture_destroy(menu->eraser_slid->back_text);
    sfTexture_destroy(menu->eraser_slid->dot_text);
    sfSprite_destroy(menu->eraser_slid->back);
    sfSprite_destroy(menu->eraser_slid->dot);
    sfTexture_destroy(menu->pen_slid->back_text);
    sfTexture_destroy(menu->pen_slid->dot_text);
    sfSprite_destroy(menu->pen_slid->back);
    sfSprite_destroy(menu->pen_slid->dot);
    free_selection(menu->selection, menu);
    free(menu);
}

static void free_image(l_image *image)
{
    sfImage_destroy(image->image);
    sfSprite_destroy(image->image_sprite);
    free_button(image->layer);
    sfTexture_destroy(image->texture);
}

static void free_layers(l_image *layer)
{
    if (layer == NULL)
        return;
    free_layers(layer->next);
    free_image(layer);
    free(layer);
}

void free_action_queue(l_action_queue *action)
{
    if (action == NULL)
        return;
    free_action_queue(action->next);
    free_layers(action->layer_list);
    free(action);
}

static void free_workspace(s_workspace *workspace)
{
    sfSprite_destroy(workspace->layer_board);
    sfSprite_destroy(workspace->work_board);
    sfTexture_destroy(workspace->layer_texture);
    sfTexture_destroy(workspace->work_texture);
    sfSprite_destroy(workspace->color_palette->palette);
    sfTexture_destroy(workspace->color_palette->texture);
    for (int i = 0; workspace->color_palette->colors[i] != NULL; i++) {
        free_button(workspace->color_palette->colors[i]);
    }
    free_action_queue(workspace->action_queue);
    free(workspace);
}

void destroy_paint(s_menubar *menubar, s_workspace *workspace)
{
    free_edition(menubar->edition);
    free_dropmenu(menubar->help);
    free_dropmenu(menubar->file);
    free_button(menubar->redo);
    free_button(menubar->undo);
    free_workspace(workspace);
    free(menubar);
}
