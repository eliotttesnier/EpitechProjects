/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** displays the number given as a parameter
*/

#include "../../include/my.h"

static int pfdisplay_number(int nb)
{
    int len = 0;
    int neg = 0;

    if (nb < 0) {
        pfmy_putchar('-');
        nb = nb * -1;
        neg = neg + 1;
    }
    if (nb > 0) {
        len = neg + pfdisplay_number(nb / 10) + 1;
        pfmy_putchar((nb % 10) + 48);
    }
    return (len);
}

int pfmy_put_nbr(int nb)
{
    if (nb == 0) {
        pfmy_putchar('0');
        return (1);
    }
    return (pfdisplay_number(nb));
}
