/*
** EPITECH PROJECT, 2023
** my_compute_power_rec
** File description:
** returns first raised to power of second recursive
*/

#include "../../include/my.h"

int pfmy_compute_power_rec(int nb, int p)
{
    int ret;

    if (p == 0)
        return (1);
    if (p < 0)
        return (0);
    if (p > 0) {
        ret = nb * pfmy_compute_power_rec(nb, p - 1);
        if (ret > 2147483647) {
            return (0);
        }
        return (ret);
    }
}
