/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** fill_pars
*/

#include "header.h"

bool is_a_comment(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t')
            return (line[i] == '#' ? true : false);
    }
    return (false);
}

bool is_a_command(char *line)
{
    char **arr = str_to_array(line, " \t\n");

    if (arr == NULL)
        return (false);
    if (my_arrlen(arr) != 1) {
        free_arr(arr);
        return (false);
    }
    if (my_strcmp("##start", arr[0]) == 1) {
        free_arr(arr);
        return (true);
    }
    if (my_strcmp("##end", arr[0]) == 1) {
        free_arr(arr);
        return (true);
    }
    free_arr(arr);
    return (false);
}

void add_node_pars(parsing_t **pars, char *line)
{
    parsing_t *new = malloc(sizeof(parsing_t) * 1);
    parsing_t *tmp = NULL;

    new->line = my_strdup(line);
    new->start = false;
    new->end = false;
    new->ignore = false;
    if (!is_a_command(new->line))
        remove_coms(new->line);
    new->next = NULL;
    if (*pars == NULL) {
        *pars = new;
        return;
    }
    for (tmp = *pars; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
}

void fill_pars(parsing_t **pars)
{
    size_t size = 0;
    char *line = NULL;

    while (true) {
        if (getline(&line, &size, stdin) == -1)
            break;
        if (!is_a_comment(line) || is_a_command(line) || line[0] == '\n')
            add_node_pars(pars, line);
        free(line);
        line = NULL;
        size = 0;
    }
    remove_commands(pars);
}
