/*
** EPITECH PROJECT, 2023
** my_putstr
** File description:
** displays, one by one, the characters of a string
*/

#include "../include/navy_header.h"

int my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
    return (my_strlen(str));
}
