/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** id_coords
*/

#include "header.h"

int same_coords(char *one, char *two)
{
    char **arr1 = str_to_array(one, " \n\t");
    char **arr2 = str_to_array(two, " \n\t");

    if (my_strcmp(arr1[1], arr2[1]) == 1 && my_strcmp(arr1[2], arr2[2]) == 1) {
        free_arr(arr1);
        free_arr(arr2);
        return (1);
    }
    free_arr(arr1);
    free_arr(arr2);
    return (0);
}

int same_id(char *one, char *two)
{
    char **arr1 = str_to_array(one, " \n\t");
    char **arr2 = str_to_array(two, " \n\t");

    if (my_strcmp(arr1[0], arr2[0]) == 1) {
        free_arr(arr1);
        free_arr(arr2);
        return (1);
    }
    free_arr(arr1);
    free_arr(arr2);
    return (0);
}

int already_room(parsing_t *pars, parsing_t *new)
{
    parsing_t *tmp = pars->next;

    while (tmp != new) {
        if (is_start(tmp) == true || is_end(tmp) == true) {
            tmp = tmp->next;
            continue;
        }
        if (same_id(tmp->line, new->line) == 1) {
            new->ignore = true;
            return (my_perror("Invalid script : Same room ID.\n", -1));
        }
        if (same_coords(tmp->line, new->line) == 1) {
            new->ignore = true;
            return (my_perror("Invalid script : Same room coords.\n", -1));
        }
        tmp = tmp->next;
    }
    return (0);
}
