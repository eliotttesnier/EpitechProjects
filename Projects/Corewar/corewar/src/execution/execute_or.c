/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_or
*/

#include "corewar_header.h"

void exec_or(map_t *vm, int value1, int value2, unsigned char reg_id)
{
    if (reg_id > 15 || value1 == -1 || value2 == -1) {
        vm->crt_prog->carry = false;
        return;
    }
    vm->crt_prog->reg[reg_id - 1] = value1 | value2;
    vm->crt_prog->carry = true;
}
