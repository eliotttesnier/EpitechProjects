/*
** EPITECH PROJECT, 2023
** my_put_scientific
** File description:
** displays a float with the scientific type
*/

#include "../../include/my.h"

int len_between_10(float nb, int decimals, char cap)
{
    int len = 4;

    len = len + my_len_float(nb, decimals);
    return (len);
}

int len_below_10(float nb, int decimals, char cap)
{
    double result = 0.00;
    int integer = (int)nb;
    int puissance = 0;
    int len = 2;

    while (integer > 9 || integer < 1) {
        puissance += 1;
        integer = (int)(nb / pfmy_compute_power_rec(10, puissance));
    }
    result = (double)(nb / pfmy_compute_power_rec(10, puissance));
    len = len + my_len_float(result, decimals);
    if (puissance < 10) {
        len += 1;
    }
    return (my_len_nbr(puissance) + len);
}

int len_above_10(float nb, int decimals, char cap)
{
    double result = 0.00;
    int integer = (int)nb;
    int puissance = 0;
    int len = 2;

    while (integer > 9 || integer < 1) {
        puissance += 1;
        integer = (int)(nb * pfmy_compute_power_rec(10, puissance));
    }
    result = (double)(nb * pfmy_compute_power_rec(10, puissance));
    len = len + my_len_float(result, decimals);
    if (puissance < 10) {
        len += 1;
    }
    return (my_len_nbr(puissance) + len);
}

int my_len_scientific(float nb, int decimals, char cap)
{
    int puissance = 0;
    int len = 0;

    if (nb < 1.00 && nb != 0.000000)
        return (len_above_10(nb, decimals, cap));
    if (nb > 9.999999)
        return (len_below_10(nb, decimals, cap));
    if (nb < 10.00 && nb >= 1.00)
        return (len_between_10(nb, decimals, cap));
    len += my_len_float(nb, decimals);
    return (len + 4);
}
