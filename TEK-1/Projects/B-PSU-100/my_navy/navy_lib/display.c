/*
** EPITECH PROJECT, 2024
** display.c
** File description:
** display game
*/

#include "../include/navy_header.h"

void disp_waiting()
{
    if (game_stat->process == 1)
        disp_maps(1);
    if (check_win() != -1)
        return;
    mini_printf("\nwaiting for enemy's attack...\n");
}

void disp(char **map)
{
    mini_printf(" |A B C D E F G H\n");
    mini_printf("-+---------------\n");
    for (int i = 0; i < 8; i++) {
        mini_printf("%i|%c", i + 1, map[i][0]);
        for (int j = 1; j < 8; j++) {
            mini_printf(" %c", map[i][j]);
        }
        mini_printf("\n");
    }
}

void disp_maps(bool force)
{
    if (force == 1 || game_stat->process == 0) {
        mini_printf("\nmy positions:\n");
        disp(game_stat->my_map);
        mini_printf("\nenemy's positions:\n");
        disp(game_stat->opp_map);
    }
}
