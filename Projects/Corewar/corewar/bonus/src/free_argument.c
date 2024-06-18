/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** free_argument
*/

#include "corewar_header.h"

void free_args(args_t *args)
{
    if (args == NULL)
        return;
    free_args(args->next);
    free(args->arg);
    free(args);
}

void free_progs(prog_pars_t *prog)
{
    if (prog == NULL)
        return;
    free_progs(prog->next);
    free(prog->path);
}

void free_arguments(argument_t *args)
{
    free_args(args->args);
    free_progs(args->progs);
}
