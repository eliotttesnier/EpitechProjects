/*
** EPITECH PROJECT, 2024
** MINISH1
** File description:
** my_strcat
*/

#include "my_lib.h"

char *my_strcat(char *one, char *two)
{
    int i = 0;
    char *new = malloc(sizeof(char) * (my_strlen(one) + my_strlen(two) + 1));

    for (i = 0; one[i] != '\0'; i++) {
        new[i] = one[i];
    }
    for (i = 0; two[i] != '\0'; i++) {
        new[my_strlen(one) + i] = two[i];
    }
    new[my_strlen(one) + i] = '\0';
    return (new);
}
