/*
** EPITECH PROJECT, 2023
** right.c
** File description:
** right input
*/

#include "../header.h"
#include "../myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

void right_space(char **map, s_player *p, char ca)
{
    map[p->x][p->y + 1] = map[p->x][p->y];
    map[p->x][p->y] = ' ';
    p->y += 1;
}

void right_box(char **map, s_player *p, char ca)
{
    char after_box = map[p->x][p->y + 2];

    if (after_box == '#' || after_box == 'X' || after_box == '1'
        || after_box == '2')
        return;
    map[p->x][p->y + 2] = map[p->x][p->y + 1];
    map[p->x][p->y + 1] = after_box;
    map[p->x][p->y + 1] = map[p->x][p->y];
    map[p->x][p->y] = ' ';
    p->y += 1;
    return;
}

void right(char **map, s_player *p)
{
    char ca = map[p->x][p->y + 1];

    if (ca == '#')
        return;
    if (ca == ' ' || ca == 'O')
        right_space(map, p, ca);
    if (ca == 'X')
        right_box(map, p, ca);
    if (ca == '1' || ca == '2')
        right_space(map, p, ca);
    return;
}
