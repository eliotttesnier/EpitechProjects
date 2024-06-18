/*
** EPITECH PROJECT, 2023
** call_put_g
** File description:
** used to call my_put_g
*/

#include <math.h>
#include <stdarg.h>
#include "../../include/my.h"

static int detect_decimals(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.')
            return (pfmy_getnbr(str, i));
    }
    return (-1);
}

int what_to_return_g(char *format, double nb, int j)
{
    if (nb < 0 && format[j] == 'g')
        return (pfmy_putstr("-inf") + 4);
    if (nb < 0 && format[j] == 'G')
        return (pfmy_putstr("-INF") + 4);
    if (format[j] == 'g')
        return (pfmy_putstr("inf") + 3);
    return (pfmy_putstr("INF") + 3);
}

int call_put_g2(char *str, double nb, int j)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-') {
            pfmy_putstr("not implemented");
            return (0);
        }
    }
    return (my_put_g(nb, detect_decimals(str), str[j]));
}

int call_put_g(char *format, va_list list, int i)
{
    double nb = va_arg(list, double);
    int test = (int)(nb * pfmy_compute_power_rec(10, 6));
    int j = i;

    if ((double)nb == 0.000000)
        nb = (double)0.000000;
    while (format[j] != 'g' && format[j] != 'G') {
        j += 1;
    }
    if (nb != nb) {
        if (format[j] == 'g') {
            return (pfmy_putstr("-nan"));
        }
        return (pfmy_putstr("-NAN"));
    }
    if (isfinite(nb) == 0)
        return (what_to_return_g(format, nb, j));
    return (call_put_g2(format, nb, j));
}
