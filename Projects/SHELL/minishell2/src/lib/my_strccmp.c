/*
** EPITECH PROJECT, 2024
** my_strccmp
** File description:
** my_strccmp
*/

#include "../../includes/header.h"

int my_strccmp(char *str, char *comp, char end)
{
    for (int i = 0; comp[i] != end; i++) {
        if (str[i] == '\0' || comp[i] == '\0')
            return (-1);
        if (str[i] != comp[i])
            return (-1);
    }
    return (0);
}
