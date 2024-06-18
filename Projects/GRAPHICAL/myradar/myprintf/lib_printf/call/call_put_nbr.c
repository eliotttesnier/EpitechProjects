/*
** EPITECH PROJECT, 2023
** call_put_nbr
** File description:
** used to call my_put_nbr
*/

#include <stdarg.h>
#include "../../include/my.h"

int plus_sign(char *current_flag, int nb)
{
    for (int i = 0; i < pfmy_strlen(current_flag); i++) {
        if (current_flag[i] == '+' && nb > 0)
            return (1);
    }
    return (0);
}

char what_char_it(char *current_flag)
{
    for (int i = 0; i < pfmy_strlen(current_flag); i++) {
        if (current_flag[i] > 48 && current_flag[i] <= 58)
            return (' ');
        if (current_flag[i] == 48)
            return ('0');
    }
    return (' ');
}

int put_pos_mods_nbr(int nb, int nb_it, char *str, int char_it)
{
    if (char_it == '0' && plus_sign(str, nb) == 1 && nb > 0)
        pfmy_putchar('+');
    if (nb < 0 && char_it == '0') {
        pfmy_putchar('-');
        nb = nb * - 1;
    }
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(char_it);
    }
    if (char_it == ' ' && plus_sign(str, nb) == 1 && nb > 0)
        pfmy_putchar('+');
    pfmy_put_nbr(nb);
}

static int put_neg_mods_nbr(int nb, int nb_it, char *current_flag)
{
    if (plus_sign(current_flag, nb) == 1 && nb > 0) {
        nb_it -= 1;
        pfmy_putchar('+');
    }
    pfmy_put_nbr(nb);
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(' ');
    }
}

int call_put_nbr(char *current_flag, va_list list, int i)
{
    int nb = va_arg(list, int);
    int nb_it = pfmy_getnbr(current_flag, 0) - my_len_nbr(nb);
    int neg_mods = 0;
    int char_it = what_char_it(current_flag);

    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == '-') {
            neg_mods = 1;
            nb_it = pfmy_getnbr(current_flag, j + 1) - my_len_nbr(nb);
            put_neg_mods_nbr(nb, nb_it, current_flag);
        }
    }
    nb_it -= plus_sign(current_flag, nb);
    if (neg_mods == 0) {
        put_pos_mods_nbr(nb, nb_it, current_flag, char_it);
    }
}
