/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** int_read
*/

#include "corewar_header.h"

int int_read(map_t *vm, int i)
{
    int one = (int)vm->map[i % MEM_SIZE] * 256 * 256 * 256;
    int two = (int)vm->map[(i + 1) % MEM_SIZE] * 256 * 256;
    int three = (int)vm->map[(i + 2) % MEM_SIZE] * 256;
    int four = (int)vm->map[(i + 3) % MEM_SIZE] * 1;

    return (one + two + three + four);
}
