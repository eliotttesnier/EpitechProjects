/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** check_flags
*/

#include "corewar_header.h"

bool warriors_after(argument_t *args, int id)
{
    args_t *tmp = args->args;

    while (tmp != NULL) {
        if (tmp->id < id)
            break;
        if (tmp->path == true)
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

args_t *get_by_id(argument_t *args, int id)
{
    args_t *tmp = args->args;

    while (tmp != NULL) {
        if (tmp->id == id)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

int check_placement(argument_t *args)
{
    args_t *tmp = args->args;

    while (tmp != NULL) {
        if (tmp->valor == true && get_by_id(args, tmp->id - 1) == NULL)
            return (my_perror("INIT: header error\n", 84));
        if (tmp->valor == true && get_by_id(args, tmp->id - 1)->flag == false)
            return (my_perror("INIT: header error\n", 84));
        if (tmp->flag == true && get_by_id(args, tmp->id + 1) == NULL)
            return (my_perror("INIT: header error\n", 84));
        if (tmp->flag == true && get_by_id(args, tmp->id + 1)->valor == false)
            return (my_perror("INIT: header error\n", 84));
        if (tmp->flag == true && !warriors_after(args, tmp->id))
            return (my_perror("INIT: arg aren't relate to any warrior\n", 84));
        tmp = tmp->next;
    }
    return (0);
}

static int check_dump(argument_t *args, args_t *tmp)
{
    args_t *valor = get_by_id(args, tmp->id + 1);

    if (my_strcmp(tmp->arg, "-a") == 1)
        return (0);
    for (int i = 0; valor->arg[i] != '\0'; i++) {
        if (IS_NBR(valor->arg[i]) == 0)
            return (my_perror("INIT: header error\n", 84));
    }
    return (0);
}

static int check_load(argument_t *args, args_t *tmp)
{
    args_t *valor = get_by_id(args, tmp->id + 1);

    if (my_strcmp(tmp->arg, "-a") == 0)
        return (0);
    for (int i = 0; valor->arg[i] != '\0'; i++) {
        if (IS_NBR(valor->arg[i]) == 0)
            return (my_perror("INIT: header error\n", 84));
    }
    return (0);
}

int check_flags(argument_t *args)
{
    args_t *tmp = args->args;

    if (check_placement(args) == 84)
        return (84);
    while (tmp != NULL) {
        if (tmp->flag == true && check_dump(args, tmp) == 84)
            return (84);
        if (tmp->flag == true && check_load(args, tmp) == 84)
            return (84);
        tmp = tmp->next;
    }
    return (0);
}
