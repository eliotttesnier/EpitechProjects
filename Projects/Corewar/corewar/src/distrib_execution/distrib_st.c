/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_st
*/

#include "corewar_header.h"

int calc_size_st(map_t *vm)
{
    int pc = vm->crt_prog->pc;
    int byte = convert_to_binary(vm->map[(pc + 1) % MEM_SIZE]);
    int nb1 = (byte / 1000000) % 100;
    int nb2 = (byte / 10000) % 100;
    int nb3 = (byte / 100) % 100;

    nb1 = (nb1 == 1 ? REG_SIZE : nb1);
    nb1 = (nb1 == 10 ? DIR_SIZE : nb1);
    nb1 = (nb1 == 11 ? IND_SIZE : nb1);
    nb2 = (nb2 == 1 ? REG_SIZE : nb2);
    nb2 = (nb2 == 10 ? DIR_SIZE : nb2);
    nb2 = (nb2 == 11 ? IND_SIZE : nb2);
    nb3 = (nb3 == 1 ? REG_SIZE : nb3);
    nb3 = (nb3 == 10 ? DIR_SIZE : nb3);
    nb3 = (nb3 == 11 ? IND_SIZE : nb3);
    return (nb1 + nb2 + nb3 + 1);
}

static int get_first_param(map_t *vm)
{
    int pc = vm->crt_prog->pc;

    return (vm->crt_prog->reg[(int)vm->map[(pc + 2) % MEM_SIZE] - 1]);
}

static int get_second_value(map_t *vm, int off)
{
    int pc = vm->crt_prog->pc;
    int t2 = convert_to_binary(vm->map[(pc + 1) % MEM_SIZE]) / 10000 % 100;

    if (t2 == 1)
        return ((int)vm->map[pc + off]);
    return (short_read(vm, pc + off));
}

int distrib_st(map_t *vm)
{
    int pc = vm->crt_prog->pc;
    int t2 = convert_to_binary(vm->map[(pc + 1) % MEM_SIZE]) / 10000 % 100;
    int p1 = get_first_param(vm);
    int p2 = get_second_value(vm, 3);

    if (t2 == 11)
        exec_st_nbr(vm, p1, p2);
    else
        exec_st_reg(vm, p1, p2);
    return (calc_size_st(vm) + 1);
}
