/*
** EPITECH PROJECT, 2024
** free_arr
** File description:
** free_arr
*/

#include "header.h"

void free_arr(char **arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}
