/*
** EPITECH PROJECT, 2023
** swap
** File description:
** sort the chained list
*/

#include "libshell/shell.h"

int swap_first(void *data, llist_t *list, llist_t *temp1, llist_t *temp2)
{
    temp1 = list;
    temp2 = list->next->next;
    list = list->next;
    ((organiz *)data)->list = list;
    list->next = temp1;
    list->next->next = temp2;
    return (0);
}

int swap(void *data, int id)
{
    llist_t *list = ((organiz *)data)->list;
    llist_t *temp1 = list;
    llist_t *temp2 = list;
    llist_t *temp3 = list;

    if (list->id == id)
        return (swap_first(data, list, temp1, temp2));
    while (list->next != NULL) {
        if (list->next->id == id) {
            temp1 = list->next;
            temp2 = list->next->next;
            temp3 = list->next->next->next;
            list->next = temp2;
            list->next->next = temp1;
            list->next->next->next = temp3;
            return (0);
        }
        list = list->next;
    }
    return (-1);
}
