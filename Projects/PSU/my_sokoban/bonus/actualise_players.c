/*
** EPITECH PROJECT, 2023
** actualise_players.c
** File description:
** actualises players positions if needed
*/

#include "header.h"
#include "myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

void check_p2(char **map, int x, int y, s_player *p2)
{
    if (x == p2->x && y == p2->y)
        map[x][y] = '2';
}

void check_p1(char **map, int x, int y, s_player *p1)
{
    if (x == p1->x && y == p1->y)
        map[x][y] = '1';
}

int actualise_players(char **map, int nb_lines, s_player *p1, s_player *p2)
{
    for (int x = 0; x < nb_lines; x++) {
        for (int y = 0; map[x][y] != '\n'; y++) {
            check_p2(map, x, y, p1);
            check_p1(map, x, y, p2);
        }
    }
    return (0);
}
