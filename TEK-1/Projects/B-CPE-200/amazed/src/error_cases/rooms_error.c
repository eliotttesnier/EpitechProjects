/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** number_pars
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

static int only_numbers(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (IS_NBR(line[i]) != 1)
            return (0);
    }
    return (1);
}

static int valid_content(char **arr)
{
    if (valid_id(arr[0]) == 0)
        return (my_perror("Invalid script : room name.\n", -1));
    if (only_numbers(arr[1]) == 0 || only_numbers(arr[2]) == 0)
        return (my_perror("Invalid script : room position.\n", -1));
    return (0);
}

int command_checking(parsing_t *pars, int *nb_start, int *nb_end)
{
    if (is_start(pars) == true) {
        *nb_start = *nb_start + 1;
        if (pars->end == true || pars->start == true)
            return (my_perror("Invalid script : Missing command room.\n", -1));
        if (pars->next == NULL || words_number(pars->next->line) < 3)
            return (my_perror("Invalid script : Missing start room.\n", -1));
    }
    if (is_end(pars) == true) {
        *nb_end = *nb_end + 1;
        if (pars->end == true || pars->start == true)
            return (my_perror("Invalid script : Missing command room.\n", -1));
        if (pars->next == NULL || words_number(pars->next->line) < 3)
            return (my_perror("Invalid script : Missing end room.\n", -1));
    }
    return (0);
}

static int rfree(char **arr, int ret)
{
    free_arr(arr);
    return (ret);
}

int valid_room(parsing_t *pars)
{
    char **arr = str_to_array(pars->line, " \t\n");
    static int nb_start = 0;
    static int nb_end = 0;

    if (arr == NULL)
        return (my_perror("Invalid script : Empty line.\n", -1));
    if (command_checking(pars, &nb_start, &nb_end) == -1)
        return (rfree(arr, -1));
    if (nb_start > 1 || nb_end > 1)
        return (my_perror("Invalid script : Too many start / end.\n", -1));
    if (is_start(pars) == true || is_end(pars) == true)
        return (rfree(arr, 0));
    if (my_arrlen(arr) < 3)
        return (my_perror("Invalid script : Invalid room.\n", -1));
    if (valid_content(arr) == -1)
        return (rfree(arr, -1));
    free_arr(arr);
    return (0);
}

int rooms_error(parsing_t *pars)
{
    parsing_t *tmp = pars->next;

    if (tmp == NULL)
        return (my_perror("Invalid script : No rooms.\n", -1));
    while (tmp != NULL) {
        if (words_number(tmp->line) == 2)
            return (0);
        if (valid_room(tmp) == -1)
            return (-1);
        if (already_room(pars, tmp) == -1)
            return (-1);
        mini_printf("%s", tmp->line);
        if (tmp->line[my_strlen(tmp->line) - 1] != '\n')
            write(1, "\n", 1);
        tmp = tmp->next;
    }
    return (0);
}
