/*
** EPITECH PROJECT, 2023
** del
** File description:
** del an element of the chained list
*/

#include "libshell/shell.h"

static void display_del(char *type, int id, char *name)
{
    my_printf("%s ", type);
    my_printf("n°%i - ", id);
    my_printf("\"%s\" deleted.\n", name);
}

int del_error_case(char **args)
{
    int nb_args = 0;

    for (nb_args = 0; args[nb_args] != NULL; nb_args++);
    if (nb_args == 0)
        return (-1);
    for (int i = 0; i < nb_args; i++) {
        if (args[i][0] > '9' || args[i][0] < '0')
            return (-1);
    }
    return (nb_args);
}

int deleting(void *data, int id)
{
    llist_t *list = ((organiz *)data)->list;
    llist_t *tmp = ((organiz *)data)->list;

    if (list->id == id) {
        ((organiz *)data)->list = list->next;
        display_del(list->type, list->id, list->name);
        free(tmp);
        return (0);
    }
    for (list; list->next != NULL; list = list->next) {
        if (list->next->id == id) {
            display_del(list->next->type, list->next->id, list->next->name);
            tmp = list->next;
            list->next = list->next->next;
            free(tmp);
            return (0);
        }
    }
    return (0);
}

int del(void *data, char **args)
{
    int nb_args = del_error_case(args);

    if (((organiz *)data)->list == NULL)
        return (84);
    if (nb_args == -1)
        return (84);
    for (int i = 0; i < nb_args; i++) {
        deleting(data, pfmy_getnbr(args[i], 0));
    }
    return (0);
}
