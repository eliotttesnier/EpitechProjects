/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_live
*/

#include "corewar_header.h"

int distrib_live(map_t *vm)
{
    int pc = vm->crt_prog->pc;

    exec_live(vm, int_read(vm, pc + 1));
    return (DIR_SIZE + 1);
}
