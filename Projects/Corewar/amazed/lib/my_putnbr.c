/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_putnbr
*/

#include "my_lib.h"

void my_putnbr(int nbr)
{
    char *tmp = my_int_to_str(nbr);

    my_putstr(tmp);
    free(tmp);
}
