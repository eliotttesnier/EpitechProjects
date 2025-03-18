/*
** EPITECH PROJECT, 2023
** unsigned
** File description:
** d
*/

#include "../../include/my.h"

char what_char_it_uns(char *current_flag)
{
    for (int i = 0; i < pfmy_strlen(current_flag); i++) {
        if (current_flag[i] > 48 && current_flag[i] <= 58)
            return (' ');
        if (current_flag[i] == 48)
            return ('0');
    }
    return (' ');
}

int put_pos_mods_uns(unsigned int nb, int nb_it, char char_it)
{
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(char_it);
    }
    my_put_unsigned(nb);
}

static int put_neg_mods_uns(int nb, int nb_it)
{
    my_put_unsigned(nb);
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(' ');
    }
}

int call_put_unsigned(char *current_flag, va_list list, int i)
{
    unsigned int nb = va_arg(list, int);
    int nb_it = pfmy_getnbr(current_flag, 0) - my_len_unsigned(nb);
    int neg_mods = 0;
    int char_it = what_char_it_uns(current_flag);

    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == '-') {
            neg_mods = 1;
            nb_it = pfmy_getnbr(current_flag, j + 1) - my_len_unsigned(nb);
            put_neg_mods_uns(nb, nb_it);
        }
    }
    if (neg_mods == 0) {
        put_pos_mods_uns(nb, nb_it, char_it);
    }
}
