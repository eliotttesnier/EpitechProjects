/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_window
*/

#include "rpg_header.h"

void free_window(window_t *window)
{
    free(window->icon);
    sfView_destroy(window->view);
    sfRenderWindow_destroy(window->window);
    free(window);
}
