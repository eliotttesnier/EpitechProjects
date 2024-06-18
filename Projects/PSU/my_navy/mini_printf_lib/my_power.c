/*
** EPITECH PROJECT, 2023
** my_compute_power_rec
** File description:
** recursive function that returns
** the first argument raised to the power p,
** where p is the second argument
*/

#include "../include/navy_header.h"

int my_power(int nb, int p)
{
    long long_result = 1;
    int result = 1;

    if (p < 0) {
        return (0);
    }
    if (p == 0) {
        return (long_result);
    }
    long_result = nb * my_power(nb, p - 1);
    result = long_result % 2147483647;
    return (result);
}
