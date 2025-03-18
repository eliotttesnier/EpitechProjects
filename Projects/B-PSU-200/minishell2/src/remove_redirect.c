/*
** EPITECH PROJECT, 2024
** remove_redirect.c
** File description:
** remove_redirect.c
*/

#include "../includes/header.h"

char **remove_arr(char **arr, int i)
{
    char **new = malloc(sizeof(char *) * nb_elements_array(arr));
    int ind = 0;

    for (int j = 0; arr[j] != NULL; j++) {
        if (j != i) {
            new[ind] = my_strdup(arr[j]);
            ind++;
        }
    }
    new[ind] = NULL;
    free_arr(arr);
    return (new);
}

void remove_redirect(command_t *new)
{
    int i = 0;

    for (i = 0; new->args[i] != NULL; i++) {
        if (my_strcmp(new->args[i], ">") == 0 ||
            my_strcmp(new->args[i], ">>") == 0 ||
            my_strcmp(new->args[i], "<") == 0 ||
            my_strcmp(new->args[i], "<<") == 0) {
            new->args = remove_arr(new->args, i);
            new->args = remove_arr(new->args, i);
            i = i - 1;
            }
    }
}
