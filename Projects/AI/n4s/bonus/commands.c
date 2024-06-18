/*
** EPITECH PROJECT, 2024
** n4s
** File description:
** commands
*/

#include "header.h"

void start(void)
{
    dprintf(1, "start_simulation\n");
    get_output();
}

void stop(void)
{
    dprintf(1, "stop_simulation\n");
    get_output();
}

void forward(float nb, bool *end)
{
    if (nb < 0)
        dprintf(1, "CAR_BACKWARDS:%fb\n", nb * -1);
    else
        dprintf(1, "CAR_FORWARD:%fb\n", nb);
    //dprintf(2, "Speed : %f\n", nb);
    *end = reached_end(get_output());
}

void direction(float dir, bool *end)
{
    dprintf(1, "WHEELS_DIR:%f\n", dir);
    *end = reached_end(get_output());
}
