/*
** EPITECH PROJECT, 2023
** actualise_o.c
** File description:
** actualises o positions if needed
*/

#include "header.h"
#include "myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

int check_if_x(char **map, int x, int y)
{
    if (map[x][y] == 'X')
        return (1);
    return (0);
}

int check_x(char **map, int x, int y)
{
    if (map[x][y] == 'X') {
        if ((map[x - 1][y] == '#' || map[x - 1][y] == 'X') &&
            (map[x][y - 1] == '#' || map[x][y - 1] == 'X'))
                return (1);
        if ((map[x - 1][y] == '#' || map[x - 1][y] == 'X') &&
            (map[x][y + 1] == '#' || map[x][y + 1] == 'X'))
                return (1);
        if ((map[x + 1][y] == '#' || map[x + 1][y] == 'X') &&
            (map[x][y - 1] == '#' || map[x][y - 1] == 'X'))
                return (1);
        if ((map[x + 1][y] == '#' || map[x + 1][y] == 'X') &&
            (map[x][y + 1] == '#' || map[x][y + 1] == 'X'))
                return (1);
    }
    return (0);
}

int check_stuck(char **map, int nb_lines)
{
    int stuck = 0;
    int nb_x = 0;

    for (int x = 0; x < nb_lines; x++) {
        for (int y = 0; map[x][y] != '\n'; y++) {
            nb_x += check_if_x(map, x, y);
            stuck += check_x(map, x, y);
        }
    }
    if (stuck == nb_x)
        return (-1);
    return (0);
}
