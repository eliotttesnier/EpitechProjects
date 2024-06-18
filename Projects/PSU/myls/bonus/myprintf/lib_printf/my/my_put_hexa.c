/*
** EPITECH PROJECT, 2023
** my_put_hexa
** File description:
** displays an unsigned int in hexa
*/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "../../include/my.h"

int display_hexa_low(unsigned int nb)
{
    char base[] = "0123456789abcdef";
    int a;

    if (nb == 0) {
        return (0);
    } else {
        a = 1 + display_hexa_low(nb / 16);
        pfmy_putchar(base[(nb % 16)]);
        return (a);
    }
}

int display_hexa_up(unsigned int nb)
{
    char base[] = "0123456789ABCDEF";
    int a;

    if (nb == 0) {
        return (0);
    } else {
        a = 1 + display_hexa_up(nb / 16);
        pfmy_putchar(base[(nb % 16)]);
        return (a);
    }
}

int my_put_hexa(unsigned int nb, int cap)
{
    char base[] = "0123456789ABCDEF";

    if (nb == base[0] - 48) {
        pfmy_putchar(base[0]);
        return (1);
    } else {
        if (cap == 0) {
            return (display_hexa_low(nb));
        } else {
            return (display_hexa_up(nb));
        }
    }
}
