/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** displays the number given as a parameter
*/

#include "../../include/my.h"

static int len_number(int nb)
{
    int len = 0;
    int neg = 0;

    if (nb < 0) {
        nb = nb * -1;
        neg = neg + 1;
    }
    if (nb > 0) {
        len = neg + len_number(nb / 10) + 1;
    }
    return (len);
}

int my_len_nbr(int nb)
{
    if (nb == 0) {
        return (1);
    }
    return (len_number(nb));
}
