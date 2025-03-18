/*
** EPITECH PROJECT, 2023
** find_player.c
** File description:
** find the player's position
*/

#include "header.h"
#include "myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

void check_player(char **map, s_player *p, int x, int y)
{
    if (map[x][y] == 'P') {
        p->x = x;
        p->y = y;
    }
}

void find_player(char **map, s_player *p, int nb_lines)
{
    for (int x = 0; x < nb_lines; x++) {
        for (int y = 0; map[x][y] != '\n'; y++) {
            check_player(map, p, x, y);
        }
    }
}
