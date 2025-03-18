/*
** EPITECH PROJECT, 2024
** B-CPE-200-NAN-2-1-amazed-noah.auroy
** File description:
** del_in_array
*/

#include "header.h"

char **del_in_array(char **arr, int index)
{
    char **new_arr = NULL;
    int j = 0;

    if (index < 0 || index >= my_arrlen(arr))
        return arr;
    new_arr = malloc(sizeof(char *) * my_arrlen(arr));
    if (new_arr == NULL)
        return NULL;
    for (int i = 0; arr[i] != NULL; i++) {
        if (i == index)
            continue;
        new_arr[j] = my_strdup(arr[i]);
        j++;
    }
    new_arr[j] = NULL;
    free_arr(arr);
    return new_arr;
}
