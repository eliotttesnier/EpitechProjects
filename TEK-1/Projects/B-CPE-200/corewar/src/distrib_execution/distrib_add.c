/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** distrib_add
*/

#include "corewar_header.h"

int calc_size_add(map_t *vm)
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

int distrib_add(map_t *vm)
{
    int pc = vm->crt_prog->pc;
    int val1 = vm->crt_prog->reg[vm->map[(pc + 2) % MEM_SIZE] - 1];
    int val2 = vm->crt_prog->reg[vm->map[(pc + 3) % MEM_SIZE] - 1];
    int id3 = (int)vm->map[(pc + 4) % MEM_SIZE];

    exec_add(vm, val1, val2, id3);
    return (calc_size_add(vm) + 1);
}
