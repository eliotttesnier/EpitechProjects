/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** my_strcmp
*/

#include "../../includes/header.h"

int my_strcmp(char *str1, char *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);

    if (len1 != len2)
        return (-1);
    for (int i = 0; i < len1; i++) {
        if (str1[i] != str2[i])
            return (-1);
    }
    return (0);
}
