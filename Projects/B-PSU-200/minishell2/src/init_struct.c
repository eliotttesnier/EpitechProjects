/*
** EPITECH PROJECT, 2024
** init_struct
** File description:
** init_struct
*/

#include "../includes/header.h"

void add_redi(command_t **redi, char *line, int fd, int in)
{
    command_t *temp = *redi;
    command_t *new = malloc(sizeof(command_t) * 1);

    new->in = in;
    new->fd = fd;
    new->args = str_to_array(line, " \t");
    remove_redirect(new);
    new->bin = my_strdup(new->args[0]);
    new->next = NULL;
    new->redi = NULL;
    new->func = NULL;
    for (temp = temp; temp->redi != NULL; temp = temp->redi);
    temp->redi = new;
}

static int is_there_char(char *line)
{
    if (line == NULL)
        return (0);
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t')
            return (1);
    }
    return (0);
}

static int nb_pipe(char *line)
{
    int nb = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '|')
            nb++;
    }
    return (nb);
}

static int nb_elems(char **arr)
{
    int nb = 0;

    for (int i = 0; arr[i] != NULL; i++) {
        if (is_there_char(arr[i]) == 1)
            nb++;
    }
    return (nb);
}

static int invalid_pipe(char *line)
{
    int nb = nb_pipe(line);
    char **arr = str_to_array(line, "|");
    int elem = nb_elems(arr);

    free_arr(arr);
    if (elem != nb + 1)
        return (my_perror("Invalid null command.\n", 1));
    return (0);
}

static void put_to_null(command_t *com)
{
    com->func = NULL;
    com->next = NULL;
    com->redi = NULL;
}

void add_node(command_t **lcom, char *line)
{
    command_t *temp = *lcom;
    command_t *new = malloc(sizeof(command_t) * 1);
    char **commands = str_to_array(line, "|");

    check_redirections(new, line);
    if (invalid_pipe(line) == 1)
        return;
    new->args = str_to_array(commands[0], " \t");
    remove_redirect(new);
    put_to_null(new);
    new->bin = my_strdup(new->args[0]);
    for (int i = 1; commands[i] != NULL; i++) {
        add_redi(&new, commands[i], new->fd, new->in);
    }
    *lcom = new;
    free_arr(commands);
}

int process_command(char *line, env_t *env, int sdin, int sdout)
{
    command_t *lcom = NULL;
    char **arr = str_to_array(line, ";\n");
    int ret = 0;

    if (is_there_char(arr[0]) == 0)
        return (0);
    for (int i = 0; arr[i] != NULL; i++) {
        add_node(&lcom, arr[i]);
        if (lcom == NULL)
            return (1);
        ret = find_func(lcom, env);
        free_lcom(lcom, sdin, sdout);
        if (ret != 0) {
            free_arr(arr);
            return (ret);
        }
    }
    free_arr(arr);
    return (0);
}
