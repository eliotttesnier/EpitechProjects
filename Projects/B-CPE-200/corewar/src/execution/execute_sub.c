/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_sub
*/

#include "corewar_header.h"

void exec_sub(map_t *vm, int value1, int value2, unsigned char reg_id)
{
    if (value1 == -1 || value2 == -1 || reg_id > 15) {
        vm->crt_prog->carry = false;
        return;
    }
    vm->crt_prog->reg[reg_id - 1] = (unsigned char)value1 - value2;
    vm->crt_prog->carry = true;
}
