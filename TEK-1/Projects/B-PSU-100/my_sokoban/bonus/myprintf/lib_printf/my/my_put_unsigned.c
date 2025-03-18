/*
** EPITECH PROJECT, 2023
** my_put_unsigned
** File description:
** d
*/

#include "../../include/my.h"

static int display_number(unsigned int nb)
{
    int len = 0;

    if (nb == 0)
        return (0);
    len = len + display_number(nb / 10) + 1;
    pfmy_putchar((nb % 10) + 48);
    return (len);
}

int my_put_unsigned(unsigned int nb)
{
    if (nb == 0) {
        pfmy_putchar('0');
        return (1);
    }
    return (display_number(nb));
}
