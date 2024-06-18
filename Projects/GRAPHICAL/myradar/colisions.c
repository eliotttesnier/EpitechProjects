/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main file
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"
#include <stdio.h>

static corner create_corn(int left, int top, int width, int height)
{
    corner create;

    create.area.height = height;
    create.area.left = left;
    create.area.top = top;
    create.area.width = width;
    create.list = NULL;
    return (create);
}

int is_overlap(list_planes **p1, list_planes **p2)
{
    sfVector2f l1 = sfSprite_getPosition((*p1)->plane);
    sfVector2f r1 = (sfVector2f){l1.x + 20, l1.y + 20};
    sfVector2f l2 = sfSprite_getPosition((*p2)->plane);
    sfVector2f r2 = (sfVector2f){l2.x + 20, l2.y + 20};

    if (r1.x < l2.x || r2.x < l1.x)
        return (0);
    if (l1.y > r2.y || l2.y > r1.y)
        return (0);
    return (1);
}

int compare(list_planes **arr)
{
    if (arr[0] == NULL || arr[1] == NULL)
        return (0);
    for (int i = 0; arr[i + 1] != NULL; i++) {
        if (is_overlap(&arr[i], &arr[i + 1]) == 1) {
            arr[i]->exploded = sfTrue;
            arr[i + 1]->exploded = sfTrue;
        }
    }
    return (0);
}

int cols_table(list_planes **planes, corner screen)
{
    list_planes *l_planes = (*planes)->next;
    sfIntRect ar = screen.area;
    sfVector2f pos;

    screen.list = malloc(sizeof(list_planes *) * 1000);
    screen.list[0] = NULL;
    screen.list[1] = NULL;
    for (int i = 0; l_planes != NULL; l_planes = l_planes->next) {
        pos = sfSprite_getPosition(l_planes->plane);
        if ((int)pos.x >= ar.left && (int)pos.x <= ar.left + ar.width + 20 &&
        (int)pos.y >= ar.top && (int)pos.y <= ar.top + ar.height + 20 &&
        l_planes->presence == sfTrue && l_planes->in_radius == sfFalse) {
            screen.list[i] = l_planes;
            screen.list[i + 1] = NULL;
            i++;
        }
    }
    compare(screen.list);
    free(screen.list);
    return (0);
}

int recursive_divide(list_planes **planes, corner screen, int times)
{
    int hh = (int)(screen.area.height / 2);
    int hw = (int)(screen.area.width / 2);
    sfIntRect area = screen.area;
    corner SO;
    corner SE;
    corner NO;
    corner NE;

    if (times == 0)
        return cols_table(planes, screen);
    SO = create_corn(area.left, area.top, hw, hh);
    recursive_divide(planes, SO, times - 1);
    SE = create_corn(area.left + hw, area.top, hw, hh);
    recursive_divide(planes, SE, times - 1);
    NO = create_corn(area.left, area.top + hh, hw, hh);
    recursive_divide(planes, NO, times - 1);
    NE = create_corn(area.left + hw, area.top + hh, hw, hh);
    recursive_divide(planes, NE, times - 1);
}

void check_cols(list_planes **planes)
{
    corner full_screen = create_corn(0, 0, 1920, 1080);

    recursive_divide(planes, full_screen, 5);
}
