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

int check_char(char **map, int x, int y, s_ocase *ocase)
{
    if (map[x][y] == ' ') {
        map[x][y] = 'O';
        ocase->status = 0;
    }
    if (map[x][y] == 'X')
        ocase->status = 1;
    return (0);
}

void actualise(char **map, int x, int y, s_ocase **ocases)
{
    for (int i = 0; ocases[i] != NULL; i++) {
        if (ocases[i]->x == x && ocases[i]->y == y) {
            check_char(map, x, y, ocases[i]);
        }
    }
}

int actualise_o(char **map, int nb_lines, s_ocase **ocases)
{
    for (int x = 0; x < nb_lines; x++) {
        for (int y = 0; map[x][y] != '\n'; y++) {
            actualise(map, x, y, ocases);
        }
    }
    display_map(map, nb_lines);
    for (int i = 0; ocases[i] != NULL; i++) {
        if (ocases[i]->status == 0)
            return (0);
    }
    return (1);
}
