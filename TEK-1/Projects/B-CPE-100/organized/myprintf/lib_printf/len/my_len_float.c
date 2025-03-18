/*
** EPITECH PROJECT, 2023
** my_put_float
** File description:
** displays a float
*/

#include <stdio.h>
#include <stdarg.h>
#include "../../include/my.h"

int len_zero(double nb, int decimals)
{
    int to_print;
    int len = 0;

    for (int i = 1; i < decimals; i++) {
        to_print = (int)(nb * pfmy_compute_power_rec(10, i));
        to_print = to_print % 10;
        if (to_print != 00)
            break;
        len += 1;
    }
    return (len);
}

int len_decimal(double nb, int decimals)
{
    int number = (int)(nb * pfmy_compute_power_rec(10, decimals));
    int check = (int)(nb * pfmy_compute_power_rec(10, decimals + 1));

    number = number % pfmy_compute_power_rec(10, decimals);
    check = check % 10;
    if (number < 0)
        number = number * (- 1);
    if (check >= 5)
        number += 1;
    return (len_zero(nb, decimals) + my_len_nbr(number) + 1);
}

int my_len_float(double nb, int decimals)
{
    int lenght = 0;
    int integer = (int)nb;

    if (nb > -1.00 && nb < 0.00) {
        lenght += 1;
    }
    if (decimals > 6 || decimals == -1)
        decimals = 6;
    if (decimals == 0)
        return (my_len_nbr(integer));
    lenght = lenght + my_len_nbr(integer);
    lenght = lenght + len_decimal(nb, decimals);
    return (lenght);
}
