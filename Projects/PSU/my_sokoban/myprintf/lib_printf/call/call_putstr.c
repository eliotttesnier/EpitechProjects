/*
** EPITECH PROJECT, 2023
** call_putstr
** File description:
** used to call putstr
*/

#include <stdarg.h>
#include "../../include/my.h"

static int put_neg_mods(char *str, int nb_it)
{
    pfmy_putstr(str);
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(' ');
    }
}

int call_putstr(char *current_flag, va_list list, int i)
{
    char *str = va_arg(list, char *);
    int nb_it = pfmy_getnbr(current_flag, 0) - pfmy_strlen(str);
    int neg_mods = 0;

    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == '-') {
            neg_mods = 1;
            nb_it = pfmy_getnbr(current_flag, j + 1) - pfmy_strlen(str);
            put_neg_mods(str, nb_it);
        }
    }
    if (neg_mods == 0) {
        for (int j = 0; j < nb_it; j++) {
            pfmy_putchar(' ');
        }
        pfmy_putstr(str);
    }
}
