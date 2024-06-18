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

void move_one_plane(list_planes *list)
{
    sfVector2f pos = sfSprite_getPosition(list->plane);

    pos.x += list->incrX / 10;
    pos.y += list->incrY / 10;
    sfSprite_setPosition(list->plane, pos);
    sfRectangleShape_setPosition(list->hitbox, pos);
}

void move_planes(all_lists *all_l)
{
    list_planes *copy = all_l->l_planes->next;
    sfTime time;
    double current;

    time = sfClock_getElapsedTime(all_l->mtime);
    current = time.microseconds / 100000;
    if (current < 1.00)
        return;
    while (copy != NULL) {
        if (copy->presence == sfTrue)
            move_one_plane(copy);
        copy = copy->next;
    }
    sfClock_restart(all_l->mtime);
    return;
}
