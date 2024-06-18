/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_fork
*/

#include "corewar_header.h"

int distrib_fork(map_t *vm)
{
    int pc = vm->crt_prog->pc;

    exec_fork(vm, int_read(vm, pc + 1));
    return (IND_SIZE + 1);
}
