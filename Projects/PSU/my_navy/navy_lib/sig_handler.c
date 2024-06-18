/*
** EPITECH PROJECT, 2024
** NAVY
** File description:
** sig_handler
*/

#include "../include/navy_header.h"

static void my_get_line(char *buffer)
{
    size_t size = 32;

    mini_printf("\nattack: ");
    getline(&buffer, &size, stdin);
}

void right_pos(int sig, siginfo_t *info, void *context)
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};

    game_stat->opp_map[game_stat->y - 1][game_stat->x - 1] = 'x';
    mini_printf("\nresult: %c%d:hit\n", game_stat->x + 64, game_stat->y);
    game_stat->x = 0;
    game_stat->y = 0;
    act.sa_sigaction = &get_x_co;
    sigaction(10, &act, NULL);
    act.sa_sigaction = &get_y_co;
    sigaction(12, &act, NULL);
    kill(game_stat->pid, 10);
    usleep(1500);
    disp_waiting();
}

void wrong_pos(int sig, siginfo_t *info, void *context)
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};

    if (game_stat->opp_map[game_stat->y - 1][game_stat->x - 1] != 'x')
        game_stat->opp_map[game_stat->y - 1][game_stat->x - 1] = 'o';
    mini_printf("\nresult: %c%d:missed\n", game_stat->x + 64, game_stat->y);
    game_stat->x = 0;
    game_stat->y = 0;
    act.sa_sigaction = &get_y_co;
    sigaction(12, &act, NULL);
    act.sa_sigaction = &get_x_co;
    sigaction(10, &act, NULL);
    kill(game_stat->pid, 10);
    usleep(1500);
    disp_waiting();
}

void get_turn(int sig, siginfo_t *info, void *context)
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};
    char *buffer = malloc(sizeof(char) * 32);

    disp_maps(0);
    if (check_win() != -1)
        return;
    while (1) {
        my_get_line(buffer);
        if (check_input(buffer) == 1) {
            break;
        } else
            mini_printf("\nwrong position\n");
    }
    game_stat->x = (int)buffer[0] - 64;
    game_stat->y = (int)buffer[1] - 48;
    act.sa_sigaction = &right_pos;
    sigaction(10, &act, NULL);
    act.sa_sigaction = &wrong_pos;
    sigaction(12, &act, NULL);
    send_coords((int)buffer[0] - 64, (int)buffer[1] - 48);
}

void get_x_co(int sig, siginfo_t *info, void *context)
{
    game_stat->x++;
}

void get_y_co(int sig, siginfo_t *info, void *context)
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};

    game_stat->y++;
    act.sa_sigaction = &check_impact;
    sigaction(10, &act, NULL);
}
