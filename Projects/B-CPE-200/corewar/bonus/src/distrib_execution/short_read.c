/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** short_read
*/

#include "corewar_header.h"

int short_read(map_t *vm, int i)
{
    int one = (int)vm->map[i % MEM_SIZE] * 256;
    int two = (int)vm->map[(i + 1) % MEM_SIZE] * 1;

    return (one + two);
}
