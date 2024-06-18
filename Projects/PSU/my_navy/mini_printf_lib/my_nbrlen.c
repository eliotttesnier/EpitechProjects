/*
** EPITECH PROJECT, 2024
** SECURED
** File description:
** my_nbrlen
*/

#include "../include/navy_header.h"

int my_nbrlen(int nbr)
{
    int i = 0;

    for (i; nbr != 0; i++) {
        nbr = nbr / 10;
    }
    return (i);
}
