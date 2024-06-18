/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_putstr
*/

#include "../include/my_lib.h"

void my_putstr(char *str)
{
    write(1, str, my_strlen(str));
}
