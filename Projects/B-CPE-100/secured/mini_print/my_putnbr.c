/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** displays the number given as a parameter
*/

#include "../include/secured.h"

static int display(int nb)
{
    my_putchar(nb + 48);
}

static int my_put_nbr_rec(long nb)
{
    int new;
    int remain;

    if (nb < 10) {
        display(nb);
        return (0);
    }
    new = nb / 10;
    remain = nb % 10;
    my_put_nbr_rec(new);
    display(remain);
}

int my_put_nbr(int nb)
{
    long nb_long;

    nb_long = nb;
    if (nb < 0) {
        nb_long = nb_long * (-1);
        my_putchar('-');
    }
    my_put_nbr_rec(nb_long);
    return (0);
}
