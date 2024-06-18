/*
** EPITECH PROJECT, 2023
** call_putchar
** File description:
** used to call my_putchar
*/

#include <stdarg.h>
#include "../../include/my.h"

static int put_neg_mods(int cha, int nb_it)
{
    pfmy_putchar(cha);
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(' ');
    }
}

int call_putchar(char *current_flag, va_list list, int i)
{
    int cha = va_arg(list, int);
    int nb_it = pfmy_getnbr(current_flag, 0) - 1;
    int neg_mods = 0;

    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == '-') {
            neg_mods = 1;
            nb_it = pfmy_getnbr(current_flag, j + 1) - 1;
            put_neg_mods(cha, nb_it);
        }
    }
    if (neg_mods == 0) {
        for (int j = 0; j < nb_it; j++) {
            pfmy_putchar(' ');
        }
        pfmy_putchar(cha);
    }
}
