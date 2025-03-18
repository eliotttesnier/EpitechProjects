/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_strcut
*/

#include "../include/my_lib.h"

char *my_strcut(char *str, int start, int end)
{
    char *new = malloc(sizeof(char) * (end - start + 1) + 1);

    if (start >= my_strlen(str) || end > my_strlen(str))
        return ("");
    if (end == -1)
        end = my_strlen(str) - 1;
    for (int i = 0; i != end - start + 1; i++) {
        new[i] = str[start + i];
    }
    new[end - start + 1] = '\0';
    return (new);
}
