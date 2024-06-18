/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_sti
*/

#include "corewar_header.h"

void exec_sti(map_t *vm, int value1, int value2, int value3)
{
    if (value1 == -1 || value2 == -1 || value3 == -1)
        return;
    vm->map[(vm->crt_prog->pc + (value2 + value3) % IDX_MOD) % MEM_SIZE]
        = value3;
    vm->idmap[(vm->crt_prog->pc + (value2 + value3) % IDX_MOD) % MEM_SIZE]
        = vm->crt_prog->id;
}
