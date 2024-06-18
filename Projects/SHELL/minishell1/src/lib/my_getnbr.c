/*
** EPITECH PROJECT, 2023
** my_getnbr
** File description:
** returns a number sent as a string
*/

#include "../../includes/header.h"

int my_getnbr(char const *str, int i)
{
    int sign = 1;
    int result = 0;

    for (i; str[i] != '\0' && (str[i] > '9' || str[i] < '0'); i++);
    if (i != 0) {
        if (str[i - 1] == '-')
            sign = -1;
    }
    for (i; str[i] != '\0' && (str[i] <= '9' && str[i] >= '0'); i++) {
        result = result * 10;
        result += str[i] - 48;
    }
    return (result * sign);
}
