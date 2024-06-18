/*
** EPITECH PROJECT, 2023
** my_strcpy
** File description:
** Copies a string into another
*/

#include "../include/secured.h"

char *my_strcpy(char *src)
{
    char *dest = malloc(sizeof(char) * (my_strlen(src) + 1));

    if (dest == NULL)
        return NULL;
    for (int i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[my_strlen(src)] = '\0';
    return (dest);
}
