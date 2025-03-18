/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_strcmp
*/

#include "../include/my_paint_header.h"

int my_strcmp(char *one, char *two)
{
    if (my_strlen(one) != my_strlen(two))
        return (0);
    for (int i = 0; one[i] != '\0' && two[i] != '\0'; i++) {
        if (one[i] != two[i])
            return (0);
    }
    return (1);
}
