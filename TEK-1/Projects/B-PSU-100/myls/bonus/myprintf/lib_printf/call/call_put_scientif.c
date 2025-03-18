/*
** EPITECH PROJECT, 2023
** call_put_scientif
** File description:
** used to call my_scientific
*/

#include <math.h>
#include <stdarg.h>
#include "../../include/my.h"

int plus_sign_s(char *current_flag, double nb)
{
    for (int i = 0; i < pfmy_strlen(current_flag); i++) {
        if (current_flag[i] == '+' && nb >= 0)
            return (1);
    }
    return (0);
}

static int calc_decimals(char *current_flag)
{
    for (int i = 0; i < pfmy_strlen(current_flag); i++) {
        if (current_flag[i] == '.')
            return (pfmy_getnbr(current_flag, i));
    }
    return (6);
}

int put_pos_mods_s(double nb, int nb_it, char *str, int char_it)
{
    int len = pfmy_strlen(str) - 1;
    int alt = 0;
    int decimals = calc_decimals(str);

    if ((str[0] == '#' || str[1] == '#') && decimals == 0) {
        alt = 1;
        nb_it -= 1;
    }
    if (char_it == '0' && plus_sign_s(str, nb) == 1)
        pfmy_putchar('+');
    if (nb < 0 && char_it == '0') {
        pfmy_putchar('-');
        nb = (double)(nb * - 1);
    }
    for (int j = 0; j < nb_it ; j++) {
        pfmy_putchar(char_it);
    }
    if (char_it == ' ' && plus_sign_s(str, nb) == 1)
        pfmy_putchar('+');
    my_put_scientific(nb, decimals, str[len], alt);
}

static int put_neg_mods_s(double nb, int nb_it, char *current_flag)
{
    int len = pfmy_strlen(current_flag);
    int alt = 0;
    int decimals = calc_decimals(current_flag);

    if ((current_flag[0] == '#' || current_flag[1] == '#')
        && decimals == 0) {
        alt = 1;
        nb_it -= 1;
    }
    if (plus_sign_s(current_flag, nb) == 1 && nb >= 0.00) {
        nb_it -= 1;
        pfmy_putchar('+');
    }
    my_put_scientific(nb, decimals, current_flag[len -1], alt);
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(' ');
    }
}

int put_scientific_mod(char *current_flag, double nb, int i)
{
    int decimals = calc_decimals(current_flag);
    int len_s = my_len_scientific(nb, decimals, 'e');
    int nb_it = pfmy_getnbr(current_flag, 0) - len_s;
    int neg_mods = 0;
    int char_it = what_char_it(current_flag);

    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == '-') {
            neg_mods = 1;
            nb_it = pfmy_getnbr(current_flag, j + 1) - len_s;
            put_neg_mods_s(nb, nb_it, current_flag);
        }
    }
    nb_it -= plus_sign_s(current_flag, nb);
    if (neg_mods == 0) {
        put_pos_mods_s(nb, nb_it, current_flag, char_it);
    }
}

static int what_to_return_s(char *format, float nb, int j)
{
    if (nb < 0 && format[j] == 'e')
        return (pfmy_putstr("-inf") + 4);
    if (nb < 0 && format[j] == 'E')
        return (pfmy_putstr("-INF") + 4);
    if (format[j] == 'e')
        return (pfmy_putstr("inf") + 3);
    return (pfmy_putstr("INF") + 3);
}

double negative_test(double nb)
{
    double result = (double)nb;

    if (nb < 0.00) {
        pfmy_putchar('-');
        result = (double)(nb * (-1));
    }
    return (result);
}

int call_put_scientific(char *format, va_list list, int i)
{
    double nb = va_arg(list, double);
    int test = (int)(nb * pfmy_compute_power_rec(10, 6));
    int j = 0;
    int neg = 0;

    if ((float)nb == 0.000000)
        nb = (float)0.000000;
    if (nb < 0.00)
        neg += 1;
    while (format[j] != 'e' && format[j] != 'E') {
        j += 1;
    }
    if (nb != nb) {
        if (format[j] == 'e')
            return (pfmy_putstr("-nan"));
        return (pfmy_putstr("-NAN"));
    }
    if (isfinite(nb) == 0)
        return (what_to_return_s(format, nb, j));
    put_scientific_mod(format, nb, i);
}
