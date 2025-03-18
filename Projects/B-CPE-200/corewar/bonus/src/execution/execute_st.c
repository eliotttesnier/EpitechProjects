/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_st
*/

#include "corewar_header.h"

void exec_st_reg(map_t *vm, int value, unsigned char reg_id)
{
    if (value == -1 || reg_id > 15)
        return;
    vm->crt_prog->reg[reg_id - 1] = value;
}

void exec_st_nbr(map_t *vm, int value, int adress)
{
    if (value == -1)
        return;
    vm->map[((vm->crt_prog->pc + adress) % IDX_MOD) % MEM_SIZE] = value;
    vm->idmap[((vm->crt_prog->pc + adress) % IDX_MOD) % MEM_SIZE]
        = vm->crt_prog->id;
}
