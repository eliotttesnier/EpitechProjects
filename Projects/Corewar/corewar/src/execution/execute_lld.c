/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_lld
*/

#include "corewar_header.h"

void exec_lld(map_t *vm, int value, unsigned char reg_id)
{
    if (reg_id > 15) {
        vm->crt_prog->carry = false;
        return;
    }
    vm->crt_prog->reg[reg_id - 1] =
        vm->map[(vm->crt_prog->pc + value) % MEM_SIZE] * 256 +
        vm->map[(vm->crt_prog->pc + value + 1) % MEM_SIZE];
    vm->crt_prog->carry = true;
}
