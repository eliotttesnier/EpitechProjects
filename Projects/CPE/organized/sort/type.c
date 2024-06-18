/*
** EPITECH PROJECT, 2023
** type
** File description:
** type sort
*/

#include "../libshell/shell.h"

int compares_type(llist_t *list, char **args, int ind)
{
    int len_a = pfmy_strlen(list->type);
    int len_b = pfmy_strlen(list->next->type);
    int len_min = len_a;

    if (len_b < len_a)
        len_min = len_b;
    for (int i = 0; i < len_min; i++) {
        if (list->type[i] > list->next->type[i])
            return (1);
        if (list->type[i] < list->next->type[i])
            return (0);
    }
    return (multiple(list, args, ind));
}

static int is_tree_type(void *data, char **args)
{
    llist_t *copy = ((organiz *)data)->list;

    while (copy->next != NULL) {
        if (compares_type(copy, args, 0) == 1)
            return (0);
        copy = copy->next;
    }
    return (1);
}

int sort_type(void *data, char **args)
{
    llist_t *copy = ((organiz *)data)->list;

    if (is_tree_type(data, args) == 1)
        return (0);
    while (copy->next != NULL) {
        if (compares_type(copy, args, 0) == 1) {
            swap(data, copy->id);
        }
        copy = copy->next;
        if (copy == NULL && is_tree_type(data, args) == 0)
            copy = ((organiz *)data)->list;
        if (copy == NULL && is_tree_type(data, args) == 1)
            break;
        if (copy->next == NULL && is_tree_type(data, args) == 0)
            copy = ((organiz *)data)->list;
    }
    return (0);
}

int compares_type_r(llist_t *list, char **args, int ind)
{
    int len_a = pfmy_strlen(list->type);
    int len_b = pfmy_strlen(list->next->type);
    int len_min = len_a;

    if (len_b < len_a)
        len_min = len_b;
    for (int i = 0; i < len_min; i++) {
        if (list->type[i] > list->next->type[i])
            return (0);
        if (list->type[i] < list->next->type[i])
            return (1);
    }
    return (multiple(list, args, ind));
}

static int is_tree_type_r(void *data, char **args)
{
    llist_t *copy = ((organiz *)data)->list;

    while (copy->next != NULL) {
        if (compares_type_r(copy, args, 0) == 1)
            return (0);
        copy = copy->next;
    }
    return (1);
}

int sort_type_r(void *data, char **args)
{
    llist_t *copy = ((organiz *)data)->list;

    if (is_tree_type_r(data, args) == 1)
        return (0);
    while (copy->next != NULL) {
        if (compares_type_r(copy, args, 1) == 1)
            swap(data, copy->id);
        copy = copy->next;
        if (copy == NULL && is_tree_type_r(data, args) == 0)
            copy = ((organiz *)data)->list;
        if (copy == NULL && is_tree_type_r(data, args) == 1)
            break;
        if (copy->next == NULL && is_tree_type_r(data, args) == 0)
            copy = ((organiz *)data)->list;
    }
    return (0);
}
