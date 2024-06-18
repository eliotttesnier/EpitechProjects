/*
** EPITECH PROJECT, 2023
** disp
** File description:
** disp the chained list
*/

#include "libshell/shell.h"

int disp(void *data, char **args)
{
    llist_t *list = ((organiz *)data)->list;

    if (args[0] != NULL)
        return (84);
    while (list != NULL) {
        my_printf("%s ", list->type);
        my_printf("n°%i - ", list->id);
        my_printf("\"%s\"\n", list->name);
        list = list->next;
    }
    return (0);
}
