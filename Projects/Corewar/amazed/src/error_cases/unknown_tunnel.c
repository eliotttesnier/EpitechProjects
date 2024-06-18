/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** unkown_tunnel
*/

#include "header.h"

int known_id(char *one, char *two, int ind)
{
    char **arr1 = str_to_array(one, " \t\n-");
    char **arr2 = str_to_array(two, " \n\t-");

    if (my_strcmp(arr1[0], arr2[ind]) == 1) {
        free_arr(arr1);
        free_arr(arr2);
        return (1);
    }
    free_arr(arr1);
    free_arr(arr2);
    return (0);
}

int unknown_tunnel(parsing_t *pars, parsing_t *new)
{
    parsing_t *tmp = pars->next;
    bool first = 0;
    bool second = 0;

    while (tmp != NULL) {
        if (words_number(tmp->line) == 2)
            break;
        if (known_id(tmp->line, new->line, 0) == 1)
            first = true;
        if (known_id(tmp->line, new->line, 1) == 1)
            second = true;
        tmp = tmp->next;
    }
    if (first == true && second == true)
        return (0);
    new->ignore = true;
    return (my_perror("Warning : Unknown room id.\n", -1));
}
