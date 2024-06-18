/*
** EPITECH PROJECT, 2023
** my_put_unsigned
** File description:
** d
*/

#include "../../include/my.h"

static int len_number_u(unsigned int nb)
{
    int len = 0;

    if (nb == 0)
        return (0);
    len = len + len_number_u(nb / 10) + 1;
    return (len);
}

int my_len_unsigned(unsigned int nb)
{
    if (nb == 0) {
        return (1);
    }
    return (len_number_u(nb));
}
