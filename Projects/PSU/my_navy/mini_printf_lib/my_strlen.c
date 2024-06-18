/*
** EPITECH PROJECT, 2023
** my_strlen
** File description:
** counts and returns the number of characters
** found in the string passed in parameter
*/

#include "../include/navy_header.h"

int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0') {
        len++;
    }
    return (len);
}
