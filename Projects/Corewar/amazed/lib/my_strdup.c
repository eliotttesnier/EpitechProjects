/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_strdup
*/

#include "my_lib.h"

char *my_strdup(char *str)
{
    char *new = malloc(sizeof(char) * (my_strlen(str) + 1));

    if (new == NULL || str == NULL)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++) {
        new[i] = str[i];
    }
    new[my_strlen(str)] = '\0';
    return (new);
}
