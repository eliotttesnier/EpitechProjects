/*
** EPITECH PROJECT, 2024
** NAVY
** File description:
** send_coords
*/

#include "../include/navy_header.h"

void send_coords(int x, int y)
{
    for (int i = 0; i < x; i++) {
        kill(game_stat->pid, 10);
        usleep(1500);
    }
    for (int i = 0; i < y; i++) {
        kill(game_stat->pid, 12);
        usleep(1500);
    }
    kill(game_stat->pid, 10);
    usleep(1500);
}
