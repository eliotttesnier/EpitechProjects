/*
** EPITECH PROJECT, 2024
** little to big
** File description:
** little to big
*/

#include "include/robot_header.h"

int check_endian(void)
{
    unsigned int x = 1;
    char *c = (char *)&x;

    return (int)*c;
}

short little_to_big_s(short num)
{
    return ((num >> 8) & 0xff) |
        ((num << 8) & 0xff00);
}

unsigned int little_to_big_u(unsigned int num)
{
    return ((num >> 24) & 0xff) |
        ((num << 8) & 0xff0000) |
        ((num >> 8) & 0xff00) |
        ((num << 24) & 0xff000000);
}
