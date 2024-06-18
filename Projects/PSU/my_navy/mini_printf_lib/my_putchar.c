/*
** EPITECH PROJECT, 2023
** my_putchar
** File description:
** Displays the character put in parameter
*/

#include "../include/navy_header.h"

int my_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}
