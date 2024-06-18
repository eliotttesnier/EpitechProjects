/*
** EPITECH PROJECT, 2024
** check_win
** File description:
** check if the game is finished
*/

#include "../include/navy_header.h"

int is_a_x(int i, int j, char **map)
{
    if (map[i][j] == 'x')
        return (1);
    return (0);
}

int check_win(void)
{
    int opp_nb_x = 0;
    int own_nb_x = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            opp_nb_x += is_a_x(i, j, game_stat->opp_map);
            own_nb_x += is_a_x(i, j, game_stat->my_map);
        }
    }
    if (opp_nb_x == 14)
        return (1);
    if (own_nb_x == 14)
        return (0);
    return (-1);
}
