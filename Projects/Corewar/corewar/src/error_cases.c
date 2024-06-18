/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** error_cases
*/

#include "corewar_header.h"

void add_node_args(argument_t *args, int i, char **av)
{
    args_t *new = malloc(sizeof(args_t) * 1);

    new->arg = my_strdup(av[i]);
    new->path = false;
    new->flag = false;
    new->valor = false;
    new->id = i - 1;
    if (my_strcmp(av[i], "-dump") == 1 || my_strcmp(av[i], "-a") == 1
        || my_strcmp(av[i], "-n") == 1)
        new->flag = true;
    if (is_there_char(av[i], '.'))
        new->path = true;
    if (new->flag == false && new->path == false)
        new->valor = true;
    new->next = args->args;
    args->args = new;
}

void fill_args(argument_t *args, char **av)
{
    for (int i = 1; av[i] != NULL; i++) {
        add_node_args(args, i, av);
    }
}

int error_cases(int ac, char **av, argument_t *args)
{
    if (ac < 3)
        return (my_perror("INIT: Too few warrior\n", 84));
    fill_args(args, av);
    if (check_for_warriors(args) == 84)
        return (84);
    if (check_flags(args) == 84)
        return (84);
    return (0);
}
