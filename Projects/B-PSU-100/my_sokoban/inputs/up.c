/*
** EPITECH PROJECT, 2023
** up.c
** File description:
** up input
*/

#include "../header.h"
#include "../myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

void up_space(char **map, s_player *p, char ca)
{
    map[p->x - 1][p->y] = map[p->x][p->y];
    map[p->x][p->y] = ' ';
    p->x -= 1;
}

void up_box(char **map, s_player *p, char ca)
{
    char after_box = map[p->x - 2][p->y];

    if (after_box == '#' || after_box == 'X')
        return;
    map[p->x - 2][p->y] = map[p->x - 1][p->y];
    map[p->x - 1][p->y] = after_box;
    map[p->x - 1][p->y] = map[p->x][p->y];
    map[p->x][p->y] = ' ';
    p->x -= 1;
    return;
}

void up_input(char **map, s_player *p)
{
    char ca = map[p->x - 1][p->y];

    if (ca == '#')
        return;
    if (ca == ' ' || ca == 'O')
        up_space(map, p, ca);
    if (ca == 'X')
        up_box(map, p, ca);
    return;
}
