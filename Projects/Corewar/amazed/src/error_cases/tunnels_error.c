/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** TUNN_pars
*/

#include "header.h"

static int valid_id(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (IS_NBR(line[i]) != 1 && IS_LCASE(line[i]) != 1
            && IS_UCASE(line[i]) != 1)
            return (0);
    }
    return (1);
}

static int nb_hyphen(char *line)
{
    int nb = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '-')
            nb++;
    }
    return (nb);
}

int valid_tunnel(parsing_t *pars)
{
    char **arr = str_to_array(pars->line, " \t\n-");

    if (arr == NULL && pars->next == NULL)
        return (my_perror("Invalid script : empty line.\n", -1));
    if (my_arrlen(arr) != 2)
        return (my_perror("Invalid script : tunnel arguments.\n", -1));
    if (valid_id(arr[0]) == 0 || valid_id(arr[1]) == 0)
        return (my_perror("Invalid script : room id.\n", -1));
    if (nb_hyphen(pars->line) != 1)
        return (my_perror("Invalid script : tunnel arguments.\n", -1));
    free_arr(arr);
    return (0);
}

parsing_t *get_first_tunnel(parsing_t *pars)
{
    parsing_t *tmp = pars->next;

    while (tmp != NULL) {
        if (words_number(tmp->line) == 2)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

int tunnels_error(parsing_t *pars)
{
    parsing_t *tmp = get_first_tunnel(pars);

    if (tmp == NULL)
        return (my_perror("Invalid script : No tunnels.\n", -1));
    while (tmp != NULL) {
        if (valid_tunnel(tmp) == -1)
            return (-1);
        if (unknown_tunnel(pars, tmp) == -1) {
            tmp = tmp->next;
            continue;
        }
        mini_printf("%s", tmp->line);
        if (tmp->line[my_strlen(tmp->line) - 1] != '\n')
            write(1, "\n", 1);
        tmp = tmp->next;
    }
    return (0);
}
