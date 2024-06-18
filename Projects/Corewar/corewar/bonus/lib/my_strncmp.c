/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_strncmp
*/

#include "../include/my_lib.h"

int my_strncmp(char *one, char *two, int nb)
{
    if (my_strlen(one) < nb || my_strlen(two) < nb)
        return (-1);
    for (int i = 0; i < nb; i++) {
        if (one[i] != two[i])
            return (-1);
    }
    return (0);
}
