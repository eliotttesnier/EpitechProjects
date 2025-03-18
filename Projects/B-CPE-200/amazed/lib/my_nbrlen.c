/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_nbrlen
*/

#include "my_lib.h"

int my_nbrlen(int nbr)
{
    int sign = 1;
    int i = 0;

    if (nbr < 0)
        sign = -1;
    for (i = i; ABS(nbr) > 0; i++) {
        nbr = nbr / 10;
    }
    return (i * sign);
}
