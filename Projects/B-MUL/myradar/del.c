/*
** EPITECH PROJECT, 2023
** move_planes.c
** File description:
** move planes
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"

static int free_towers(list_towers **towers)
{
    if ((*towers) == NULL)
        return (0);
    free_towers(&(*towers)->next);
    free((*towers));
    return (0);
}

void free_struct(all_lists *all_l, background_s *back)
{
    free(all_l->l_planes);
    sfSprite_destroy(back->back);
    sfTexture_destroy(back->texture);
    free_towers(&all_l->l_towers);
}

void del_temp(list_planes **list)
{
    list_planes *tmp = (*list);

    *list = (*list)->next;
    free(tmp);
}

void add_temp(list_planes **list)
{
    list_planes *new = malloc(sizeof(list_planes));

    new->next = *list;
    *list = new;
}

void del(list_planes **list)
{
    list_planes *tmp = (*list)->next;

    (*list)->next = (*list)->next->next;
    sfRectangleShape_destroy(tmp->hitbox);
    sfSprite_destroy(tmp->plane);
    sfTexture_destroy(tmp->texture);
    return;
}
