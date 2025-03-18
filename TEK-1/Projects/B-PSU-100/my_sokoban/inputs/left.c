/*
** EPITECH PROJECT, 2023
** left.c
** File description:
** left input
*/

#include "../header.h"
#include "../myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

void left_space(char **map, s_player *p, char ca)
{
    map[p->x][p->y - 1] = map[p->x][p->y];
    map[p->x][p->y] = ' ';
    p->y -= 1;
}

void left_box(char **map, s_player *p, char ca)
{
    char after_box = map[p->x][p->y - 2];

    if (after_box == '#' || after_box == 'X')
        return;
    map[p->x][p->y - 2] = map[p->x][p->y - 1];
    map[p->x][p->y - 1] = after_box;
    map[p->x][p->y - 1] = map[p->x][p->y];
    map[p->x][p->y] = ' ';
    p->y -= 1;
    return;
}

void left(char **map, s_player *p)
{
    char ca = map[p->x][p->y - 1];

    if (ca == '#')
        return;
    if (ca == ' ' || ca == 'O')
        left_space(map, p, ca);
    if (ca == 'X')
        left_box(map, p, ca);
    return;
}
