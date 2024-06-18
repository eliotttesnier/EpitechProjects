/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_lfork
*/

#include "corewar_header.h"

int distrib_lfork(map_t *vm)
{
    int pc = vm->crt_prog->pc;

    exec_lfork(vm, int_read(vm, pc + 1));
    return (IND_SIZE + 1);
}
