/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_zjmp
*/

#include "corewar_header.h"

void exec_zjmp(map_t *vm, int value)
{
    if (vm->crt_prog->carry == false) {
        return;
    }
    vm->crt_prog->pc =
        (vm->crt_prog->pc + value % IDX_MOD - (value > MEM_SIZE ? 512 : 0))
        % MEM_SIZE;
}
