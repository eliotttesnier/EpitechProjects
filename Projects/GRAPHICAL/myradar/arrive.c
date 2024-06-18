/*
** EPITECH PROJECT, 2023
** arrive.c
** File description:
** arrive
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"

void check_arrive(list_planes **list)
{
    list_planes *copy = *list;
    sfVector2f pos = sfSprite_getPosition((*list)->next->plane);
    double speed = copy->next->speed;

    while (copy->next != NULL) {
        pos = sfSprite_getPosition(copy->next->plane);
        speed = copy->next->speed;
        if ((copy->next->exploded == sfTrue) ||
        (pos.x - speed < copy->next->ax && pos.x + speed > copy->next->ax &&
        pos.y - speed < copy->next->ay && pos.y + speed > copy->next->ay)) {
            del(&copy);
        } else
            copy = copy->next;
    }
}
