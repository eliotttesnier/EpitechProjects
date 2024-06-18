/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_ld
*/

#include "corewar_header.h"

void exec_ld(map_t *vm, int value, unsigned char reg_id)
{
    if (reg_id > 15) {
        vm->crt_prog->carry = false;
        return;
    }
    vm->crt_prog->reg[reg_id - 1] =
        vm->map[((vm->crt_prog->pc) + value % IDX_MOD) % MEM_SIZE] * 256 +
        vm->map[((vm->crt_prog->pc) + value % IDX_MOD + 1) % MEM_SIZE];
    vm->crt_prog->carry = true;
}
