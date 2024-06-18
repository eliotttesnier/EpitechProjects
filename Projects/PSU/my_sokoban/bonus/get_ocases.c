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

static int fill_struct(int x, int y, int i, s_ocase **ocases)
{
    if (x == -1)
        return (0);
    ocases[i]->x = x;
    ocases[i]->y = y;
    ocases[i]->status = 0;
    return (0);
}

static int check_ocase(char **map, int x, int y)
{
    if (map[x][y] == 'O')
        return (1);
    return (0);
}

int calc_nb_ocases(char **map, int nb_lines)
{
    int nb_ocases = 0;

    for (int x = 0; x < nb_lines; x++) {
        for (int y = 0; map[x][y] != '\n'; y++) {
            nb_ocases += check_ocase(map, x, y);
        }
    }
    return (nb_ocases);
}

void fill_ocase(char **map, s_ocase **ocases, int nb_lines)
{
    int o = 0;
    int i = 0;

    for (int x = 0; x < nb_lines; x++) {
        for (int y = 0; map[x][y] != '\n'; y++) {
            o += check_ocase(map, x, y);
            fill_struct( (o == 0) ? -1 : x, y, i, ocases);
            i += o;
            o = 0;
        }
    }
}

s_ocase **get_ocases(char **map, s_ocase **ocases, int nb_lines)
{
    int nb_ocases = calc_nb_ocases(map, nb_lines);

    ocases = malloc(sizeof(s_ocase) * nb_ocases + 1);
    for (int i = 0; i < nb_ocases; i++) {
        ocases[i] = malloc(sizeof(s_ocase));
    }
    fill_ocase(map, ocases, nb_lines);
    ocases[nb_ocases] = NULL;
    return (ocases);
}
