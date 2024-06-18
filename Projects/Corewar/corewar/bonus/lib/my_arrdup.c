/*
** EPITECH PROJECT, 2024
** MINISH1
** File description:
** my_arrcpy
*/

#include "../include/my_lib.h"

char **my_arrdup(char **arr)
{
    int len;
    char **new;

    for (len = 0; arr[len] != NULL; len++);
    new = malloc(sizeof(char *) * (len + 1));
    new[len] = NULL;
    for (int i = 0; arr[i] != NULL; i++) {
        new[i] = my_strdup(arr[i]);
    }
    return (new);
}
