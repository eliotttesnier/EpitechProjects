/*
** EPITECH PROJECT, 2023
** my_strlen
** File description:
** counts the number of characters in the string
*/

#include "../../include/my.h"

int pfmy_strlen(char const *str)
{
    int lenght = 0;

    while (str[lenght] != '\0') {
        lenght = lenght + 1;
    }
    return (lenght);
}
