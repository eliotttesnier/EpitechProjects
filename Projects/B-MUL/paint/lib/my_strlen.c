/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_strlen
*/

#include "../include/my_paint_header.h"

int my_strlen(char *str)
{
    int i = 0;

    if (str == NULL)
        return (-1);
    for (i = 0; str[i] != '\0'; i++);
    return (i);
}
