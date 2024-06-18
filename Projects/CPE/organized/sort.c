/*
** EPITECH PROJECT, 2023
** sort
** File description:
** sort the chained list
*/

#include "libshell/shell.h"

static int verif_name(char *str, char *name)
{
    for (int i = 0; i < 4; i++) {
        if (str[i] != name[i])
            return (0);
    }
    return (1);
}

static int verif_type(char *str, char *type)
{
    for (int i = 0; i < 4; i++) {
        if (str[i] != type[i])
            return (0);
    }
    return (1);
}

int verif_sort(char *str)
{
    int verif = 0;
    int len = pfmy_strlen(str);
    char type[5] = "TYPE";
    char name[5] = "NAME";

    if (len == 4) {
        if (verif_type(str, type) == 1)
            return (0);
        if (verif_name(str, name) == 1)
            return (0);
    }
    if (len == 2) {
        if (str[0] == '-' && str[1] == 'r')
            return (0);
        if (str[0] == 'I' && str[1] == 'D')
            return (0);
    }
    return (-1);
}

int sort_error_case(char **args, void *data)
{
    int nb_args = 0;

    if (((organiz *)data)->list == NULL)
        return (-1);
    for (nb_args = 0; args[nb_args] != NULL; nb_args++);
    if (nb_args == 0 || nb_args > 6)
        return (-1);
    if (args[0][0] == '-')
        return (-1);
    for (int i = 0; i < nb_args; i++) {
        if (verif_sort(args[i]) == -1)
            return (-1);
    }
    return (nb_args);
}

int call_tree_one(void *data, char **args)
{
    if (args[0][0] == 'T')
        return (sort_type(data, args));
    if (args[0][0] == 'N')
        return (sort_name(data, args));
    if (args[0][0] == 'I')
        return (sort_id(data));
    return (84);
}

int sort(void *data, char **args)
{
    int nb_args = sort_error_case(args, data);

    if (nb_args == -1)
        return (84);
    if (nb_args == 1)
        return (call_tree_one(data, args));
    if (args[1][0] != '-')
        return (call_tree_one(data, args));
    if (args[1][0] == '-') {
        if (args[0][0] == 'T')
            return (sort_type_r(data, args));
        if (args[0][0] == 'N')
            return (sort_name_r(data, args));
        return (sort_id_r(data));
    }
    return (0);
}
