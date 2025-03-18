/*
** EPITECH PROJECT, 2023
** my_put_binary
** File description:
** display an int with binary base
*/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "../../include/my.h"

int display_binary(unsigned int nb)
{
    char base[] = "01";
    int a;

    if (nb == 0) {
        return (0);
    } else {
        a = 1 + display_binary(nb / 2);
        pfmy_putchar(base[(nb % 2)]);
        return (a);
    }
}

int my_put_binary(unsigned int nb)
{
    char base[] = "01";

    if (nb == base[0] - 48) {
        pfmy_putchar(base[0]);
        return (1);
    } else {
        return (display_binary(nb));
    }
}
