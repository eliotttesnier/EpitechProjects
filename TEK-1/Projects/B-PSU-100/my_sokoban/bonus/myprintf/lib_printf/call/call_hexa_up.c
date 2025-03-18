/*
** EPITECH PROJECT, 2023
** call_hexa_up
** File description:
** d
*/

#include <stdarg.h>
#include "../../include/my.h"

static int alt_vers(char *current_flag)
{
    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == '#') {
            pfmy_putchar('0');
            pfmy_putchar('X');
            return (0);
        }
    }
}

static int put_neg_mods(char *current_flag, unsigned int nbr, int nb_it)
{
    if (current_flag[0] == '#' || current_flag[1] == '#')
        nb_it -= 2;
    alt_vers(current_flag);
    my_put_hexa(nbr, 1);
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(' ');
    }
}

int put_pos_mods_hup(char *current_flag, int nbr, int nb_it)
{
    if (what_char_it(current_flag) == '0')
        alt_vers(current_flag);
    for (int j = 0; j < nb_it; j++) {
        pfmy_putchar(what_char_it(current_flag));
    }
    if (what_char_it(current_flag) == ' ')
        alt_vers(current_flag);
    my_put_hexa(nbr, 1);
}

int call_hexa_up(char *current_flag, va_list list, int i)
{
    unsigned int nbr = va_arg(list, unsigned int);
    int nb_it = pfmy_getnbr(current_flag, 0) - my_len_hexa(nbr, 0);
    int	neg_mods = 0;

    if (current_flag[0] == '#' || current_flag[1] == '#')
        nb_it -= 2;
    for (int j = 0; current_flag[j] != '\0'; j++) {
        if (current_flag[j] == '-') {
            neg_mods = 1;
            nb_it = pfmy_getnbr(current_flag, j + 1) - my_len_hexa(nbr, 0);
            put_neg_mods(current_flag, nbr, nb_it);
        }
    }
    if (neg_mods == 0)
        put_pos_mods_hup(current_flag, nbr, nb_it);
}
