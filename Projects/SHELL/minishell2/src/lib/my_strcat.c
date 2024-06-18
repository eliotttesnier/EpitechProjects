/*
** EPITECH PROJECT, 2024
** my_strcat.c
** File description:
** my_strcat.c
*/

#include "../../includes/header.h"

char *my_strcat(char *str1, char *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    int ind = 0;
    char *result = malloc(sizeof(char) * (len1 + len2) + 1);

    for (int i = 0; str1[i] != '\0'; i++) {
        result[ind] = str1[i];
        ind += 1;
    }
    for (int i = 0; str2[i] != '\0'; i++) {
        result[ind] = str2[i];
        ind += 1;
    }
    result[ind] = '\0';
    return result;
}
