/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** uptadte_id
*/

#include "corewar_header.h"

bool id_already_used(int id, argument_t *args, prog_pars_t *stop)
{
    prog_pars_t *tmp = args->progs;

    while (tmp != NULL) {
        if (tmp == stop)
            break;
        if (tmp->id == id)
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

int get_valid_id(int id, argument_t *args)
{
    for (; id_already_used(id, args, NULL) == true; id++);
    return (id);
}

void update_load_prog(argument_t *args)
{
    int nb_prog = args->nb_programs;
    int id = 0;

    for (prog_pars_t *tmp = args->progs; tmp != NULL; tmp = tmp->next) {
        if (tmp->load != -1) {
            id++;
            continue;
        }
        tmp->load = (MEM_SIZE / nb_prog) * id;
        id++;
    }
}

void update_id_prog(argument_t *args)
{
    prog_pars_t *tmp = args->progs;

    tmp = args->progs;
    while (tmp != NULL) {
        if (tmp->id != -1 && id_already_used(tmp->id, args, tmp))
            tmp->id = get_valid_id(tmp->id, args);
        if (tmp->id == -1)
            tmp->id = get_valid_id(0, args);
        tmp = tmp->next;
    }
}
