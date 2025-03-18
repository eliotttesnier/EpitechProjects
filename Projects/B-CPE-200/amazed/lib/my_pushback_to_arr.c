/*
** EPITECH PROJECT, 2024
** P_AMAZED
** File description:
** my_pushback_to_arr
*/

#include "my_lib.h"

char **my_pushback_to_arr(char **arr, char *new_line)
{
    char **new = malloc(sizeof(char *) * my_arrlen(arr) + 2);

    if (new_line == NULL || arr == NULL || new == NULL)
        return (NULL);
    for (int i = 0; i < my_arrlen(arr) + 1; i++) {
        new[i] = my_strdup(arr[i]);
        free(arr[i]);
    }
    new[my_arrlen(arr)] = my_strdup(new_line);
    new[my_arrlen(arr) + 1] = NULL;
    free(arr);
    return (new);
}
