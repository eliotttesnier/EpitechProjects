/*
** EPITECH PROJECT, 2024
** my_strdup.c
** File description:
** my_strdup.c
*/

#include "../../includes/header.h"

char *my_strdup(char *str)
{
    char *dup = malloc(sizeof(char) * (my_strlen(str) + 1));

    for (int i = 0; str[i] != '\0'; i++) {
        dup[i] = str[i];
        dup[i + 1] = '\0';
    }
    return (dup);
}
