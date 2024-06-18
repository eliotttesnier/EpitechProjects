/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_live
*/

#include "corewar_header.h"

void exec_live(map_t *vm, int player_nbr)
{
    vm->crt_prog->alive = true;
    vm->nb_live++;
    mini_printf("The player %d(%s)is alive.\n", player_nbr,
        vm->crt_prog->name);
}
