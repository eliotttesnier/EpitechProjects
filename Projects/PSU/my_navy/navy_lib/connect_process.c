/*
** EPITECH PROJECT, 2024
** NAVY
** File description:
** connect_process
*/

#include "../include/navy_header.h"

void confirm_connection_2(int sig, siginfo_t *info, void *context)
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};

    mini_printf("\nsuccessfully connected\n");
    act.sa_sigaction = &get_x_co;
    sigaction(10, &act, NULL);
    act.sa_sigaction = &get_y_co;
    sigaction(12, &act, NULL);
    disp_waiting();
    kill(game_stat->pid, 10);
}

void connect_to_opp_2(int pid)
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};

    mini_printf("my_pid: %d\n", getpid());
    act.sa_sigaction = &confirm_connection_2;
    game_stat->pid = pid;
    sigaction(10, &act, NULL);
    kill(pid, 10);
    pause();
}

void get_opp_pid_1(int sig, siginfo_t *info, void *context)
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};

    game_stat->pid = info->si_pid;
    act.sa_sigaction = &get_turn;
    kill(game_stat->pid, 10);
    mini_printf("\nenemy connected\n");
    sigaction(10, &act, NULL);
}

void wait_for_opp_1()
{
    struct sigaction act = {.sa_flags = SA_SIGINFO};

    mini_printf("my_pid: %d\n", getpid());
    mini_printf("\nwaiting for enemy connection...\n");
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = &get_opp_pid_1;
    sigaction(10, &act, NULL);
    pause();
}
