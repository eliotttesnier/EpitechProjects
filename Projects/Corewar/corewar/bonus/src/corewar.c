/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar
*/

#include "corewar_header.h"

void write_the_program(map_t *vm, prog_t *prog)
{
    int size = prog->size;
    int pa = prog->pa;

    for (int i = pa; i < pa + size; i++) {
        vm->map[i % MEM_SIZE] = prog->prog[i - pa];
        vm->idmap[i % MEM_SIZE] = prog->id;
    }
}

void write_prog_to_vm(map_t *vm)
{
    for (int i = 0; i < vm->nb_prog; i++) {
        write_the_program(vm, vm->programs[i]);
    }
}

int build_programs(map_t *vm, argument_t args)
{
    prog_pars_t *tmp = args.progs;

    for (int i = 0; i < vm->nb_prog && tmp != NULL; i++) {
        vm->programs[i] = build_prog(tmp->path, tmp->load, tmp->id);
        if (vm->programs[i] == NULL)
            return (84);
        tmp = tmp->next;
    }
    write_prog_to_vm(vm);
    return (0);
}

int corewar(int ac, char **av)
{
    argument_t args;
    map_t *vm;

    args.progs = NULL;
    args.args = NULL;
    if (error_cases(ac, av, &args) == 84)
        return (84);
    fill_progs(&args);
    vm = build_map(args.nb_programs, args.cycle);
    if (build_programs(vm, args) != 0)
        return (84);
    free_arguments(&args);
    simulate_loop(vm);
    return (0);
}
