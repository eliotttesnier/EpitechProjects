/*
** EPITECH PROJECT, 2024
** main
** File description:
** main for my_navy
*/

#include "../include/navy_header.h"

game_s *game_stat = NULL;

void display_win(int value)
{
    disp_maps(1);
    if (value == 1)
        mini_printf("I won\n");
    if (value == 0)
        mini_printf("Enemy won\n");
}

int main(int ac, char **av)
{
    int value = 0;

    game_stat = malloc(sizeof(game_s));
    if (hub_error(ac, av) == 84)
        return (84);
    if (ac == 3) {
        game_stat->process = 1;
        connect_to_opp_2(my_getnbr(av[1], 0));
    } else {
        game_stat->process = 0;
        wait_for_opp_1();
    }
    while (1) {
        value = check_win();
        if (value == 0 || value == 1)
            break;
    }
    display_win(value);
    return (value);
}
