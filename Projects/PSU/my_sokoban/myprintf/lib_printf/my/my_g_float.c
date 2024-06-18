/*
** EPITECH PROJECT, 2023
** my_put_float
** File description:
** displays a float
*/

#include <stdio.h>
#include <stdarg.h>
#include "../../include/my.h"

int displays_zero_g(float nb, int decimals)
{
    int to_print;
    int len = 0;

    for (int i = 1 ; i < decimals ; i++) {
        to_print = (int)(nb * pfmy_compute_power_rec(10, i));
        to_print = to_print % 10;
        if (to_print != 00)
            break;
        len += 1;
        pfmy_putchar('0');
    }
    return (len);
}

int displays_decimal_g(float nb, int decimals)
{
    int number = (int)(nb * pfmy_compute_power_rec(10, decimals));
    int check = (int)(nb * pfmy_compute_power_rec(10, decimals + 1));

    pfmy_putchar('.');
    number = number % pfmy_compute_power_rec(10, decimals);
    check = check % 10;
    if (number < 0)
        number = number * (- 1);
    if (check >= 5)
        number += 1;
    pfmy_putchar('\n');
    pfmy_put_nbr(number);
    pfmy_putchar('\n');
    return (displays_zero_g(nb, decimals) + pfmy_put_nbr(number) + 1);
}

int my_g_float(float nb, int decimals)
{
    int lenght = 0;
    int integer = (int)nb;

    if (nb > -1.00 && nb < 0.00) {
        pfmy_putchar('-');
        lenght += 1;
    }
    if (decimals == 0)
        return (pfmy_put_nbr(integer));
    lenght = lenght + pfmy_put_nbr(integer);
    lenght = lenght + displays_decimal_g(nb, decimals);
    return (lenght);
}
