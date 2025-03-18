/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_putchar
*/

#include "my_lib.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}
