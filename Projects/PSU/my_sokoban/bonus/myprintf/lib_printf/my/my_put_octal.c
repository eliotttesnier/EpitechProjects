/*
** EPITECH PROJECT, 2023
** put_octal
** File description:
** display an int with octal base
*/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "../../include/my.h"

int display_octal(unsigned int nb)
{
    char base[] = "01234567";
    int a;

    if (nb == 0) {
        return (0);
    } else {
        a = 1 + display_octal(nb / 8);
        pfmy_putchar(base[(nb % 8)]);
        return (a);
    }
}

int my_put_octal(unsigned int nb)
{
    char base[] = "01234567";

    if (nb == base[0] - 48) {
        pfmy_putchar(base[0]);
        return (1);
    } else {
        return (display_octal(nb));
    }
}
