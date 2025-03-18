/*
** EPITECH PROJECT, 2023
** mutliple_comp
** File description:
** multiple comparison
*/

#include "../libshell/shell.h"

int multiple_second(llist_t *list, char **args, int ind)
{
    if (args[ind + 1][0] == 'T')
        return (compares_type(list, args, ind + 1));
    if (args[ind + 1][0] == 'N')
        return (compares_name(list, args, ind + 1));
    return (compares_id(list));
}

int multiple(llist_t *list, char **args, int ind)
{
    if (args[ind + 1] == NULL)
        return (0);
    if (args[ind + 2] == NULL) {
        if (args[ind + 1][0] == 'T')
            return (compares_type(list, args, ind + 1));
        if (args[ind + 1][0] == 'N')
            return (compares_name(list, args, ind + 1));
        return (compares_id(list));
    }
    if (args[ind + 2][0] == '-') {
        if (args[ind + 1][0] == 'T')
            return (compares_type_r(list, args, ind + 2));
        if (args[ind + 1][0] == 'N')
            return (compares_name_r(list, args, ind + 2));
        return (compares_id_r(list));
    }
    return (multiple_second(list, args, ind));
}
