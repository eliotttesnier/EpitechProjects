/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_lldi
*/

#include "corewar_header.h"

int calc_size_lldi(map_t *vm)
{
    int pc = vm->crt_prog->pc;
    int byte = convert_to_binary(vm->map[(pc + 1) % MEM_SIZE]);
    int nb1 = (byte / 1000000) % 100;
    int nb2 = (byte / 10000) % 100;
    int nb3 = (byte / 100) % 100;

    nb1 = (nb1 == 1 ? REG_SIZE : nb1);
    nb1 = (nb1 == 10 ? IND_SIZE : nb1);
    nb1 = (nb1 == 11 ? IND_SIZE : nb1);
    nb2 = (nb2 == 1 ? REG_SIZE : nb2);
    nb2 = (nb2 == 10 ? IND_SIZE : nb2);
    nb2 = (nb2 == 11 ? IND_SIZE : nb2);
    nb3 = (nb3 == 1 ? REG_SIZE : nb3);
    nb3 = (nb3 == 10 ? IND_SIZE : nb3);
    nb3 = (nb3 == 11 ? IND_SIZE : nb3);
    return (nb1 + nb2 + nb3 + 1);
}

static int get_first_value(map_t *vm, int *off)
{
    int pc = vm->crt_prog->pc;
    int byte = convert_to_binary(vm->map[(pc + 1) % MEM_SIZE]);
    int nb1 = (byte / 1000000) % 100;

    if (nb1 == 1) {
        *off = *off + 1;
        return (vm->crt_prog->reg[vm->map[(pc + 2) % MEM_SIZE] - 1]);
    }
    *off = *off + 2;
    return (short_read(vm, pc + 2));
}

static int get_second_value(map_t *vm, int *off)
{
    int pc = vm->crt_prog->pc;
    int byte = convert_to_binary(vm->map[(pc + 1) % MEM_SIZE]);
    int nb2 = (byte / 10000) % 100;

    if (nb2 == 1) {
        *off = *off + 1;
        return (vm->crt_prog->reg[vm->map[(pc + 2 + *off) % MEM_SIZE] - 1]);
    }
    *off = *off + 2;
    return (short_read(vm, pc + 2 + *off));
}

int distrib_lldi(map_t *vm)
{
    int pc = vm->crt_prog->pc;
    int off = 0;
    int val1 = get_first_value(vm, &off);
    int val2 = get_second_value(vm, &off);
    int id3 = (int)vm->map[(pc + 2 + off) % MEM_SIZE];

    exec_lldi(vm, val1, val2, id3);
    return (calc_size_lldi(vm) + 1);
}
