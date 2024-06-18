/*
** EPITECH PROJECT, 2023
** id
** File description:
** id sort
*/

#include "../libshell/shell.h"

static int is_tree_id(void *data)
{
    llist_t *copy = ((organiz *)data)->list;

    while (copy->next != NULL) {
        if (copy->id > copy->next->id)
            return (0);
        copy = copy->next;
    }
    return (1);
}

int compares_id(llist_t *list)
{
    if (list->id > list->next->id)
        return (1);
    return (0);
}

int sort_id(void *data)
{
    llist_t *copy = ((organiz *)data)->list;

    if (is_tree_id(data) == 1)
        return (0);
    while (copy->next != NULL) {
        if (compares_id(copy) == 1)
            swap(data, copy->id);
        copy = copy->next;
        if (copy == NULL && is_tree_id(data) == 0)
            copy = ((organiz *)data)->list;
        if (copy == NULL && is_tree_id(data) == 1)
            break;
        if (copy->next == NULL && is_tree_id(data) == 0)
            copy = ((organiz *)data)->list;
    }
    return (0);
}

static int is_tree_id_r(void *data)
{
    llist_t *copy = ((organiz *)data)->list;

    while (copy->next != NULL) {
        if (copy->id < copy->next->id)
            return (0);
        copy = copy->next;
    }
    return (1);
}

int compares_id_r(llist_t *list)
{
    if (list->id < list->next->id)
        return (1);
    return (0);
}

int sort_id_r(void *data)
{
    llist_t *copy = ((organiz *)data)->list;

    if (is_tree_id_r(data) == 1)
        return (0);
    while (copy->next != NULL) {
        if (compares_id_r(copy) == 1)
            swap(data, copy->id);
        copy = copy->next;
        if (copy == NULL && is_tree_id_r(data) == 0)
            copy = ((organiz *)data)->list;
        if (copy == NULL && is_tree_id_r(data) == 1)
            break;
        if (copy->next == NULL && is_tree_id_r(data) == 0)
            copy = ((organiz *)data)->list;
    }
    return (0);
}
