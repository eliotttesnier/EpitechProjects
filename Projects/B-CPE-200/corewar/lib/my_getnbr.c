/*
** EPITECH PROJECT, 2023
** BS_Radar
** File description:
** my_getnbr
*/

#include "../include/my_lib.h"

int my_getnbr(char *buff, int i)
{
    int numbers = 0;
    int sign = 1;
    int nb = 0;

    for (int j = 0; buff[j] != '\0'; j++) {
        if (buff[j] >= '0' && buff[j] <= '9')
            numbers++;
    }
    if (numbers == 0)
        return (-9);
    for (i = i; (buff[i] < '0' || buff[i] > '9') && buff[i] != '\0'; i++);
    if (i != 0) {
        if (buff[i - 1] == '-')
            sign = -1;
    }
    for (i = i; buff[i] >= '0' && buff[i] <= '9'; i++) {
        nb = nb * 10;
        nb += (buff[i] - 48);
    }
    return (nb * sign);
}
