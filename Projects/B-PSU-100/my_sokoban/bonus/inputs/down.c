/*
** EPITECH PROJECT, 2023
** down.c
** File description:
** down input
*/

#include "../header.h"
#include "../myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

void down_space(char **map, s_player *p, char ca)
{
    map[p->x + 1][p->y] = map[p->x][p->y];
    map[p->x][p->y] = ' ';
    p->x += 1;
}

void down_box(char **map, s_player *p, char ca)
{
    char after_box = map[p->x + 2][p->y];

    if (after_box == '#' || after_box == 'X' || after_box == '1'
        || after_box == '2')
        return;
    map[p->x + 2][p->y] = map[p->x + 1][p->y];
    map[p->x + 1][p->y] = after_box;
    map[p->x + 1][p->y] = map[p->x][p->y];
    map[p->x][p->y] = ' ';
    p->x += 1;
    return;
}

void down(char **map, s_player *p)
{
    char ca = map[p->x + 1][p->y];

    if (ca == '#')
        return;
    if (ca == ' ' || ca == 'O')
        down_space(map, p, ca);
    if (ca == 'X')
        down_box(map, p, ca);
    if (ca == '1' || ca == '2')
        down_space(map, p, ca);
    return;
}
