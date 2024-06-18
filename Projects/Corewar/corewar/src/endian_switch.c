/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** big_to_little
*/

#include "corewar_header.h"

unsigned int big_to_little(unsigned int num)
{
    return ((num >> 24) & 0x000000FF) |
        ((num >> 8) & 0x0000FF00) |
        ((num << 8) & 0x00FF0000) |
        ((num << 24) & 0xFF000000);
}

unsigned short little_to_big_s(unsigned short num)
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
