/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_aff
*/

#include "corewar_header.h"

int distrib_aff(map_t *vm)
{
    int pc = vm->crt_prog->pc;
    int value = (int)vm->map[(pc + 2) % MEM_SIZE];

    exec_aff(vm, vm->crt_prog->reg[value - 1]);
    return (REG_SIZE + 1 + 1);
}
