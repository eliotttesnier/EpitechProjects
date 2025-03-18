/*
** EPITECH PROJECT, 2023
** my_put_scientific
** File description:
** displays a float with the scientific type
*/

#include "../../include/my.h"

int between_10(double nb, int decimals, char cap, int alt)
{
    int len = 4;

    len = len + my_put_float(nb, decimals);
    if (decimals == 0 && alt == 1)
        pfmy_putchar('.');
    pfmy_putchar(cap);
    pfmy_putstr("+00");
    return (len);
}

int below_10(double nb, int decimals, char cap, int alt)
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
    len = len + my_put_float(result, decimals);
    if (decimals == 0 && alt == 1)
        pfmy_putchar('.');
    pfmy_putchar(cap);
    pfmy_putchar('+');
    if (puissance < 10) {
        pfmy_putchar('0');
        len += 1;
    }
    return (pfmy_put_nbr(puissance) + len);
}

int above_10(double nb, int decimals, char cap, int alt)
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
    len = len + my_put_float(result, decimals);
    if (decimals == 0 && alt == 1)
        pfmy_putchar('.');
    pfmy_putchar(cap);
    pfmy_putchar('-');
    if (puissance < 10) {
        pfmy_putchar('0');
        len += 1;
    }
    return (pfmy_put_nbr(puissance) + len);
}

int my_put_scientific(double nb, int decimals, char cap, int alt)
{
    int puissance = 0;
    int len = 0;

    if (decimals == 0 && alt == 1)
        len += 1;
    if (nb < 1.00 && nb != 0.000000)
        return (above_10(nb, decimals, cap, alt));
    if (nb > 9.999999)
        return (below_10(nb, decimals, cap, alt));
    if (nb < 10.00 && nb >= 1.00)
        return (between_10(nb, decimals, cap, alt));
    len += my_put_float(nb, decimals);
    pfmy_putchar(cap);
    pfmy_putstr("+00");
    return (len + 4);
}
