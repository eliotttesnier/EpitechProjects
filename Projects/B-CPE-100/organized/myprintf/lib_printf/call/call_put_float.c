/*
** EPITECH PROJECT, 2023
** call_put_float
** File description:
** used to call put float
*/

#include <math.h>
#include <stdarg.h>
#include "../../include/my.h"

int plus_sign_float(char *current_flag, double nb)
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

int put_pos_mods_float(double nb, int nb_it, char *str, int char_it)
{
    int alt = 0;

    if ((str[0] == '#' || str[1] == '#') && calc_decimals(str) == 0) {
        alt = 1;
        nb_it -= 1;
    }
    if (char_it == '0' && plus_sign_float(str, nb) == 1)
        pfmy_putchar('+');
    if (nb < 0 && char_it == '0') {
        pfmy_putchar('-');
        nb = (double)(nb * - 1);
    }
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(char_it);
    }
    if (char_it == ' ' && plus_sign_float(str, nb) == 1)
        pfmy_putchar('+');
    my_put_float(nb, calc_decimals(str));
    if (alt == 1)
        pfmy_putchar('.');
}

static int put_neg_mods_float(double nb, int nb_it, char *current_flag)
{
    if (plus_sign_float(current_flag, nb) == 1 && nb >= 0.00) {
        nb_it -= 1;
        pfmy_putchar('+');
    }
    my_put_float(nb, calc_decimals(current_flag));
    if ((current_flag[0] == '#' || current_flag[1] == '#')
        && calc_decimals(current_flag) == 0) {
        nb_it -= 1;
        pfmy_putchar('.');
    }
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(' ');
    }
}

int put_float_mod(char *current_flag, double nb, int i)
{
    int decimals = calc_decimals(current_flag);
    int nb_it = pfmy_getnbr(current_flag, 0) - my_len_float(nb, decimals);
    int neg_mods = 0;
    int char_it = what_char_it(current_flag);
    int len_float = my_len_float(nb, decimals);

    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == '-') {
            neg_mods = 1;
            nb_it = pfmy_getnbr(current_flag, j + 1) - len_float;
            put_neg_mods_float(nb, nb_it, current_flag);
        }
    }
    nb_it -= plus_sign_float(current_flag, nb);
    if (neg_mods == 0)
        put_pos_mods_float(nb, nb_it, current_flag, char_it);
}

static int what_to_return(char *format, float nb, int j)
{
    if (nb < 0 && format[j] == 'f')
        return (pfmy_putstr("-inf") + 4);
    if (nb < 0 && format[j] == 'F')
        return (pfmy_putstr("-INF") + 4);
    if (format[j] == 'f')
        return (pfmy_putstr("inf") + 3);
    return (pfmy_putstr("INF") + 3);
}

int call_put_float(char *current_flag, va_list list, int i)
{
    double nb = va_arg(list, double);
    int test = (int)(nb * pfmy_compute_power_rec(10, 6));
    int j = 0;

    while (current_flag[j] != 'f' && current_flag[j] != 'F') {
        j += 1;
    }
    if (nb != nb) {
        if (current_flag[j] == 'f') {
            return (pfmy_putstr("-nan"));
        }
        return (pfmy_putstr("-NAN"));
    }
    if (isfinite(nb) == 0)
        return (what_to_return(current_flag, nb, j));
    put_float_mod(current_flag, nb, i);
}
