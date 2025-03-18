/*
** EPITECH PROJECT, 2024
** check_win
** File description:
** check if the game is finished
*/

#include "../include/navy_header.h"

void check_impact(int sig, siginfo_t *info, void *context)
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};

    act.sa_sigaction = &get_turn;
    sigaction(10, &act, NULL);
    if (game_stat->my_map[game_stat->y - 1][game_stat->x - 1] >= '2' &&
    game_stat->my_map[game_stat->y - 1][game_stat->x - 1] <= '5') {
        game_stat->my_map[game_stat->y - 1][game_stat->x - 1] = 'x';
        mini_printf("\n%c%d: hit\n", game_stat->x + 64, game_stat->y);
        kill(game_stat->pid, 10);
        usleep(1500);
    } else {
        if (game_stat->my_map[game_stat->y - 1][game_stat->x - 1] != 'x')
            game_stat->my_map[game_stat->y - 1][game_stat->x - 1] = 'o';
        mini_printf("\n%c%d: missed\n", game_stat->x + 64, game_stat->y);
        kill(game_stat->pid, 12);
        usleep(1500);
    }
}
