/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** exec_programs
*/

#include "corewar_header.h"

const call_function_t func_arr[16] = {
    distrib_live,
    distrib_ld,
    distrib_st,
    distrib_add,
    distrib_sub,
    distrib_and,
    distrib_or,
    distrib_xor,
    distrib_zjmp,
    distrib_ldi,
    distrib_sti,
    distrib_fork,
    distrib_lld,
    distrib_lldi,
    distrib_lfork,
    distrib_aff,
};

void exec_single_program(map_t *vm, int i)
{
    unsigned char instru;

    for (prog_t *tmp = vm->programs[i]; tmp != NULL; tmp = tmp->next) {
        vm->crt_prog = tmp;
        instru = vm->map[tmp->pc % MEM_SIZE];
        if (instru <= 0 || instru > 16) {
            tmp->pc += 1;
            continue;
        }
        tmp->freeze_cycle -= 1;
        if (tmp->first_time == true) {
            tmp->freeze_cycle = op_tab[instru - 1].nbr_cycles;
            tmp->first_time = false;
        }
        if (tmp->freeze_cycle <= 0 && tmp->first_time == false) {
            tmp->first_time = true;
            tmp->pc = (tmp->pc + func_arr[instru - 1](vm)) % MEM_SIZE;
        }
    }
}

bool check_overwritten(map_t *vm, int nb)
{
    int id = vm->programs[nb]->id;

    for (int i = 0; i < MEM_SIZE; i++) {
        if (vm->idmap[i] == id)
            return (false);
    }
    vm->programs[nb] = NULL;
    return (true);
}

void exec_programs(map_t *vm)
{
    for (int i = 0; i < vm->nb_prog; i++) {
        if (vm->programs[i] == NULL)
            continue;
        if (!check_overwritten(vm, i))
            exec_single_program(vm, i);
    }
}
