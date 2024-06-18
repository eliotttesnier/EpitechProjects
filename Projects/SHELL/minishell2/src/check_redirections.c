/*
** EPITECH PROJECT, 2024
** check_redirections
** File description:
** check for redirections error
*/

#include "../includes/header.h"

static int nb_redir(char **arr)
{
    int nb_right = 0;
    int nb_left = 0;

    for (int i = 0; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], "<") == 0)
            nb_right++;
        if (my_strcmp(arr[i], "<<") == 0)
            nb_right++;
        if (my_strcmp(arr[i], ">") == 0)
            nb_left++;
        if (my_strcmp(arr[i], ">>") == 0)
            nb_left++;
    }
    if (nb_right > 1 || nb_left > 1)
        return (my_perror("Ambiguous input redirect.\n", -1));
    return (0);
}

int check_right(char *line)
{
    char **arr = str_to_array(line, " \t");
    int valid_redirection = valid_redir(arr);
    int nb_redirections = nb_redir(arr);
    int fd = 0;

    if (nb_redirections == -1 || valid_redirection == -1)
        return (-1);
    for (int i = 0; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], ">") == 0)
            fd = open_simple_right(arr[i + 1]);
        if (my_strcmp(arr[i], ">>") == 0)
            fd = open_double_right(arr[i + 1]);
    }
    free_arr(arr);
    return (fd);
}

int check_left(char *line, int fd)
{
    char **arr = str_to_array(line, " \t");
    int in = 0;

    if (fd == -1) {
        free_arr(arr);
        return (0);
    }
    fd = 0;
    for (int i = 0; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], "<") == 0)
            fd = open_simple_left(arr[i + 1]);
        if (my_strcmp(arr[i], "<<") == 0)
            fd = open_double_left(arr[i + 1]);
    }
    free_arr(arr);
    return (fd);
}

void check_redirections(command_t *com, char *line)
{
    com->fd = check_right(line);
    com->in = check_left(line, com->fd);
}
