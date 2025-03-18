/*
** EPITECH PROJECT, 2023
** my_sokoban.c
** File description:
** sokoban game
*/

#include "header.h"
#include "myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

void check_term_size(char **map, int nb_lines, int maxlen)
{
    int goodsize = 0;

    while (goodsize == 0) {
        mvprintw(LINES / 2, COLS / 2 - 8, "Enlarge Terminal");
        if (LINES >= nb_lines && COLS >= maxlen)
            goodsize = 1;
        refresh();
        clear();
    }
}
