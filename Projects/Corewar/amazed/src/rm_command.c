/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** rm_command
*/

#include "header.h"

bool is_start(parsing_t *pars)
{
    char **arr = NULL;

    if (pars == NULL)
        return (false);
    arr = str_to_array(pars->line, " \t\n");
    if (arr == NULL)
        return (false);
    if (my_strcmp(arr[0], "##start") == 1) {
        free_arr(arr);
        return (true);
    }
    free_arr(arr);
    return (false);
}

bool is_end(parsing_t *pars)
{
    char **arr = NULL;

    if (pars == NULL)
        return (false);
    arr = str_to_array(pars->line, " \t\n");
    if (arr == NULL)
        return (false);
    if (my_strcmp(arr[0], "##end") == 1) {
        free_arr(arr);
        return (true);
    }
    free_arr(arr);
    return (false);
}

static void set_start(parsing_t *pars)
{
    if (pars == NULL)
        return;
    pars->start = true;
}

static void set_end(parsing_t *pars)
{
    if (pars == NULL)
        return;
    pars->end = true;
}

void remove_commands(parsing_t **pars)
{
    parsing_t *tmp = *pars;

    while (tmp != NULL) {
        if (is_start(tmp) == true)
            set_start(tmp->next);
        if (is_end(tmp) == true)
            set_end(tmp->next);
        tmp = tmp->next;
    }
}
