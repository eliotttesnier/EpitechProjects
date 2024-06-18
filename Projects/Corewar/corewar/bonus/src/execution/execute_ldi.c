/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_ldi
*/

#include "corewar_header.h"

void exec_ldi(map_t *vm, int value1, int value2, unsigned char reg_id)
{
    int s = 0;

    if (reg_id > 15 || value1 == -1 || value2 == -1) {
        vm->crt_prog->carry = false;
        return;
    }
    s = vm->map[(vm->crt_prog->pc + value1 % IDX_MOD) % MEM_SIZE] * 256 +
        vm->map[(vm->crt_prog->pc + value1 % IDX_MOD + 1) % MEM_SIZE] + value2;
    vm->crt_prog->reg[reg_id - 1] =
        vm->map[(vm->crt_prog->pc + s % IDX_MOD) % MEM_SIZE] * 256
        + vm->map[(vm->crt_prog->pc + s % IDX_MOD + 1) % MEM_SIZE];
    vm->crt_prog->carry = true;
}
