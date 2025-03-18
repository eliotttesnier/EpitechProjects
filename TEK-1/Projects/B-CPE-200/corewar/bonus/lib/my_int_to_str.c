/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_int_to_str
*/

#include "../include/my_lib.h"

char *my_int_to_str(int nbr)
{
    int nb_c = ABS(my_nbrlen(nbr)) + IS_NEG(nbr);
    char *str = malloc(sizeof(char) * (nb_c + 1));

    if (nbr == 0) {
        str[0] = '0';
        str[1] = '\0';
        return (str);
    }
    if (IS_NEG(nbr) == 1)
        str[0] = '-';
    str[nb_c] = '\0';
    if (nbr == 0)
        str[0] = '0';
    for (int i = 1; nbr != 0; i++) {
        str[nb_c - i] = ABS(nbr) % 10 + 48;
        nbr = nbr / 10;
    }
    return (str);
}
