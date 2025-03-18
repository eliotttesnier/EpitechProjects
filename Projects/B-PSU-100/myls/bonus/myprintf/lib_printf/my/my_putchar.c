/*
** EPITECH PROJECT, 2023
** my_putchar
** File description:
** my_puthcar
*/

#include "../../include/my.h"
#include <unistd.h>

void pfmy_putchar(char c)
{
    write(1, &c, 1);
}
