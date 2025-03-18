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

static void game_param(char **map, s_player *p, int nb_lines, s_player *p2)
{
    find_player(map, p, nb_lines);
    p2->x = p->x;
    p2->y = p->y;
    initscr();
    curs_set(0);
    keypad(stdscr, true);
}

static void display_map(char **map, int nb_lines)
{
    for (int i = 0; i < nb_lines; i++) {
        mvprintw(0 + i, 0 , map[i]);
    }
}

static int game_loop2(char **map, s_player *p2, s_ocase **ocases, int input)
{
    if (input == 'z')
        up_input(map, p2);
    if (input == 's')
        down(map, p2);
    if (input == 'q')
        left(map, p2);
    if (input == 'd')
        right(map, p2);
    return (0);
}

int game_loop(char **map, s_player *p, s_ocase **ocases, s_player *p2)
{
    int input = getch();

    clear();
    game_loop2(map, p2, ocases, input);
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
    refresh();
    return (0);
}

int beg_game(int ac, char **av)
{
    char **map;
    s_ocase **ocases;
    int nb_lines;
    int maxlen;
    s_player player;
    s_player player2;

    map = get_map(map, av[1], &nb_lines, &maxlen);
    ocases = get_ocases(map, ocases, nb_lines);
    game_param(map, &player, nb_lines, &player2);
    while (0 == 0) {
        check_term_size(map, nb_lines, maxlen);
        if (actualise_o(map, nb_lines, ocases) == 1)
            return (0);
        if (check_stuck(map, nb_lines) != 0)
            return (1);
        actualise_players(map, nb_lines, &player, &player2);
        display_map(map, nb_lines);
        if (game_loop(map, &player, ocases, &player2) == -1) {
            return (beg_game(ac, av));
        }
    }
}

int display_issue(int ac, char **av)
{
    int issue;

    issue = beg_game(ac, av);
    if (issue == 1)
        mvprintw(0, 0, "You got stuck :(");
    if (issue == 0)
        mvprintw(0, 0, "You did it :)");
    mvprintw(1, 0, "Press 'space' to play again !");
    mvprintw(2, 0, "Press any other key to leave !");
    if (getch() == ' ')
        beg_game(ac, av);
    endwin();
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
