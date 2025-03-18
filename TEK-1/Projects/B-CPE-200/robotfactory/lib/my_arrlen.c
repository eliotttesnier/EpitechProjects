/*
** EPITECH PROJECT, 2024
** MINISH1
** File description:
** my_arrlen
*/

#include "../include/my_lib.h"

int my_arrlen(char **arr)
{
    int i = 0;

    if (arr == NULL)
        return (-1);
    for (i = 0; arr[i] != NULL; i++);
    return (i);
}
