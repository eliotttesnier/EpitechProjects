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

static void game_param(char **map, s_player *player, int nb_lines)
{
    find_player(map, player, nb_lines);
    initscr();
    curs_set(0);
    keypad(stdscr, true);
}

void display_map(char **map, int nb_lines)
{
    clear();
    for (int i = 0; i < nb_lines; i++) {
        mvprintw(0 + i, 0 , map[i]);
    }
    refresh();
}

int game_loop(char **map, s_player *p, s_ocase **ocases)
{
    int input = getch();

    if (input == ' ')
        return (-1);
    if (input == KEY_UP)
        up_input(map, p);
    if (input == KEY_DOWN)
        down(map, p);
    if (input == KEY_LEFT)
        left(map, p);
    if (input == KEY_RIGHT)
        right(map, p);
    return (0);
}

int beg_game(int ac, char **av)
{
    char **map;
    s_ocase **ocases;
    int nb_lines;
    int maxlen;
    s_player player;

    map = get_map(map, av[1], &nb_lines, &maxlen);
    ocases = get_ocases(map, ocases, nb_lines);
    game_param(map, &player, nb_lines);
    while (0 == 0) {
        check_term_size(map, nb_lines, maxlen);
        if (actualise_o(map, nb_lines, ocases) == 1)
            return (0);
        if (check_stuck(map, nb_lines) != 0)
            return (1);
        if (game_loop(map, &player, ocases) == -1) {
            return (beg_game(ac, av));
        }
    }
}

int display_issue(int ac, char **av)
{
    int issue;

    issue = beg_game(ac, av);
    curs_set(1);
    keypad(stdscr, false);
    usleep(10000);
    endwin();
    if (issue == 1)
        return (1);
    if (issue == 0)
        return (0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    if (pfmy_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h')
        return (readme());
    if (error_cases(av[1]) == -1)
        return (84);
    return (display_issue(ac, av));
}
