/*
** EPITECH PROJECT, 2023
** my_put_g
** File description:
** displays %g
*/

#include <stdio.h>
#include <stdarg.h>
#include "../../include/my.h"

int my_put_g(double nb, int decimals, char cap)
{
    int len_integer = 0;
    int len = 0;

    if (decimals == -1)
        decimals = 6;
    if (nb < 0.00)
        nb = (double)(nb * (- 1));
    len_integer = my_len_nbr((int)(nb));
    if ((int)(nb) > -1.00 && (int)(nb) < 1.00)
        len_integer -= 1;
    if (len_integer > decimals)
        return (my_put_scientific(nb, decimals - 1, cap - 2, 0));
    if (len_integer == decimals)
        return (pfmy_put_nbr((int)(nb)));
    if (len_integer < decimals)
        return (my_put_float(nb, decimals - len_integer));
}
