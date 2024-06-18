/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_zjmp
*/

#include "corewar_header.h"

int distrib_zjmp(map_t *vm)
{
    int pc = vm->crt_prog->pc;

    exec_zjmp(vm, short_read(vm, pc + 1));
    return (vm->crt_prog->pc - pc);
}
