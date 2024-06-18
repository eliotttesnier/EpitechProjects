/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** execute_fork
*/

#include "corewar_header.h"

static unsigned char *my_progdup(int size, unsigned char *prog)
{
    unsigned char *new = malloc(sizeof(unsigned) * size);

    for (int i = 0; i < size; i++) {
        new[i] = prog[i];
    }
    return (new);
}

static void fill_reg(prog_t *old, prog_t *new)
{
    for (int i = 0; i < 16; i++) {
        new->reg[i] = old->reg[i];
    }
}

static void add_new_node(map_t *vm, int value)
{
    prog_t *new = malloc(sizeof(prog_t) * 1);
    prog_t *tmp;

    new->alive = vm->crt_prog->alive;
    new->carry = vm->crt_prog->carry;
    new->first_time = vm->crt_prog->first_time;
    new->freeze_cycle = vm->crt_prog->freeze_cycle;
    new->name = my_strdup(vm->crt_prog->name);
    new->pa = (vm->crt_prog->pc + value % IDX_MOD) % MEM_SIZE;
    new->pc = new->pa + (vm->crt_prog->pc - vm->crt_prog->pa) + 3;
    new->size = vm->crt_prog->size;
    new->id = vm->crt_prog->id;
    new->prog = my_progdup(vm->crt_prog->size, vm->crt_prog->prog);
    fill_reg(vm->crt_prog, new);
    new->next = NULL;
    for (tmp = vm->crt_prog; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
}

void exec_fork(map_t *vm, int value)
{
    prog_t *last;

    add_new_node(vm, value);
    for (last = vm->crt_prog; last->next != NULL; last = last->next);
    for (int i = 0; i < last->size; i++) {
        vm->map[last->pa + i % MEM_SIZE] = last->prog[i];
        vm->idmap[last->pa + i % MEM_SIZE] = last->id;
    }
}
