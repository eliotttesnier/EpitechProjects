/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** create slider
*/

#include "rpg_header.h"

slider_t *create_slider(char *path_back, sfIntRect rect_back, char *path_dot,
    sfIntRect rect_dot)
{
    slider_t *new = malloc(sizeof(slider_t));

    new->back = create_sprite(path_back, rect_back);
    new->dot = create_sprite(path_dot, rect_dot);
    new->clicked = false;
    return new;
}
