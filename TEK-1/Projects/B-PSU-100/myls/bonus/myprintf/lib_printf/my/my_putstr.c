/*
** EPITECH PROJECT, 2023
** my_putstr
** File description:
** displays the characters of a string
*/

#include "../../include/my.h"

int pfmy_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        pfmy_putchar(str[i]);
        i = i + 1;
    }
    return (0);
}
