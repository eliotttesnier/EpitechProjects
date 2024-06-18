/*
** EPITECH PROJECT, 2023
** BS_Radar
** File description:
** my_getnbr
*/

#include "../include/navy_header.h"

int my_getnbr(char *buffer, int i)
{
    int sign = 1;
    int nb = 0;

    for (i; (buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '\0'; i++);
    if (i != 0) {
        if (buffer[i - 1] == '-')
            sign = -1;
    }
    for (i; buffer[i] >= '0' && buffer[i] <= '9'; i++) {
        nb = nb * 10;
        nb += (buffer[i] - 48);
    }
    return (nb * sign);
}
