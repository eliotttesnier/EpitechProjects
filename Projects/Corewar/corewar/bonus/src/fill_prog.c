/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** fill_prog
*/

#include "corewar_header.h"

void add_node_prog(argument_t *args, args_t *tmp)
{
    prog_pars_t *new = malloc(sizeof(prog_pars_t) * 1);

    new->path = my_strdup(tmp->arg);
    new->id = -1;
    new->load = -1;
    new->next = args->progs;
    args->progs = new;
}

void change_valor_prog(char *valor, char *flag, argument_t *args)
{
    int val = my_getnbr(valor, 0);

    if (my_strcmp("-area", flag) == 1 && args->cycle == -1)
        args->cycle = val;
    if (my_strcmp("-a", flag) == 1 && args->progs->load == -1)
        args->progs->load = val % MEM_SIZE;
    if (my_strcmp("-n", flag) == 1 && args->progs->id == -1)
        args->progs->id = val;
}

void fill_progs(argument_t *args)
{
    args_t *tmp = args->args;

    args->cycle = -1;
    while (tmp != NULL) {
        if (tmp->path == true)
            add_node_prog(args, tmp);
        if (tmp->valor == true)
            change_valor_prog(tmp->arg, tmp->next->arg, args);
        tmp = tmp->next;
    }
    update_id_prog(args);
    update_load_prog(args);
}
