/*
** EPITECH PROJECT, 2023
** type
** File description:
** type sort
*/

#include "../libshell/shell.h"

int compares_name(llist_t *list, char **args, int ind)
{
    int len_a = pfmy_strlen(list->name);
    int len_b = pfmy_strlen(list->next->name);
    int len_min = len_a;

    if (len_b < len_a)
        len_min = len_b;
    for (int i = 0; i < len_min; i++) {
        if (list->name[i] > list->next->name[i])
            return (1);
        if (list->name[i] < list->next->name[i])
            return (0);
    }
    return (multiple(list, args, ind));
}

static int is_tree_name(void *data, char **args)
{
    llist_t *copy = ((organiz *)data)->list;

    while (copy->next != NULL) {
        if (compares_name(copy, args, 0) == 1)
            return (0);
        copy = copy->next;
    }
    return (1);
}

int sort_name(void *data, char **args)
{
    llist_t *copy = ((organiz *)data)->list;

    if (is_tree_name(data, args) == 1)
        return (0);
    while (copy->next != NULL) {
        if (compares_name(copy, args, 0) == 1) {
            swap(data, copy->id);
        }
        copy = copy->next;
        if (copy == NULL && is_tree_name(data, args) == 0)
            copy = ((organiz *)data)->list;
        if (copy == NULL && is_tree_name(data, args) == 1)
            break;
        if (copy->next == NULL && is_tree_name(data, args) == 0)
            copy = ((organiz *)data)->list;
    }
    return (0);
}

int compares_name_r(llist_t *list, char **args, int ind)
{
    int len_a = pfmy_strlen(list->name);
    int len_b = pfmy_strlen(list->next->name);
    int len_min = len_a;

    if (len_b < len_a)
        len_min = len_b;
    for (int i = 0; i < len_min; i++) {
        if (list->name[i] > list->next->name[i])
            return (0);
        if (list->name[i] < list->next->name[i])
            return (1);
    }
    return (multiple(list, args, ind));
}

static int is_tree_name_r(void *data, char **args)
{
    llist_t *copy = ((organiz *)data)->list;

    while (copy->next != NULL) {
        if (compares_name_r(copy, args, 1) == 1)
            return (0);
        copy = copy->next;
    }
    return (1);
}

int sort_name_r(void *data, char **args)
{
    llist_t *copy = ((organiz *)data)->list;

    if (is_tree_name_r(data, args) == 1)
        return (0);
    while (copy->next != NULL) {
        if (compares_name_r(copy, args, 1) == 1)
            swap(data, copy->id);
        copy = copy->next;
        if (copy == NULL && is_tree_name_r(data, args) == 0)
            copy = ((organiz *)data)->list;
        if (copy == NULL && is_tree_name_r(data, args) == 1)
            break;
        if (copy->next == NULL && is_tree_name_r(data, args) == 0)
            copy = ((organiz *)data)->list;
    }
    return (0);
}
