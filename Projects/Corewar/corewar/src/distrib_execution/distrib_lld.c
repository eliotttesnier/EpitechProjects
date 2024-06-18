/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_lld
*/

#include "corewar_header.h"

int calc_size_lld(map_t *vm)
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
    int byte = convert_to_binary(vm->map[(pc + 1) % MEM_SIZE]);
    int nb1 = (byte / 1000000) % 100;

    if (nb1 == 10)
        return int_read(vm, pc + 2);
    return (short_read(vm, pc + 2));
}

static int get_second_value(map_t *vm, int off)
{
    int pc = vm->crt_prog->pc;
    int value = (int)vm->map[(pc + 1 + off) % MEM_SIZE];

    return (value);
}

int distrib_lld(map_t *vm)
{
    int pc = vm->crt_prog->pc;
    int t1 = convert_to_binary(vm->map[(pc + 1) % MEM_SIZE]) / 1000000 % 100;
    int p1 = get_first_param(vm);
    int p2 = get_second_value(vm, (t1 == 1 ? 1 : 2));

    exec_lld(vm, p1, p2);
    return (calc_size_lld(vm) + 1);
}
