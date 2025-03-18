/*
** EPITECH PROJECT, 2023
** organized
** File description:
** organize chained lists
*/

#include "libshell/shell.h"

void free_list(llist_t *list)
{
    if (list == NULL)
        return;
    free_list(list->next);
    free(list->name);
    free(list->type);
    free(list);
}

int organized(int ac, char **av)
{
    organiz orga;

    orga.max_id = -1;
    orga.list = NULL;
    if (workshop_shell(&orga) == 84)
        return (84);
    free_list(orga.list);
    return (0);
}
