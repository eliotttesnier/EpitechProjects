/*
** EPITECH PROJECT, 2024
** process
** File description:
** process
*/

#include "../includes/header.h"

const exec_t commands[6] = {
    {"exit", exit_func},
    {"cd", cd_func},
    {"env", env_func},
    {"unsetenv", unsetenv_func},
    {"setenv", setenv_func},
    {NULL, NULL}};

void check_builtin(command_t *com)
{
    for (int i = 0; commands[i].func != NULL; i++) {
        if (my_strcmp(com->bin, commands[i].name) == 0)
            com->func = commands[i].func;
    }
}

int find_func(command_t *com, env_t *env)
{
    int ret = 0;

    if (com->fd == -1 || com->in == -1)
        return (1);
    if (com->bin[0] == '\0')
        return (0);
    for (command_t *tmp = com; tmp != NULL; tmp = tmp->redi) {
        check_builtin(com);
        if (tmp->func == NULL)
            ret = check_path(tmp, env);
        if (ret == 1)
            return (1);
    }
    return (before_exec(com, env));
}

int user_process(env_t *env, int sdin, int sdout)
{
    size_t size = 0;
    char *com = NULL;

    while (1) {
        write(1, "\x1b[32m$> \x1b[0m", 12);
        getline(&com, &size, stdin);
        process_command(com, env, sdin, sdout);
        com = NULL;
    }
    return (0);
}

int echo_process(env_t *env, int sdin, int sdout)
{
    size_t size = 0;
    char *com = NULL;
    int ret = 0;

    while (1 && ret == 0) {
        getline(&com, &size, stdin);
        if (com[0] == '\0')
            break;
        ret = process_command(com, env, sdin, sdout);
        com = NULL;
    }
    return (ret);
}

int minishell(int ac, char **av, env_t *env)
{
    int sdin = dup(STDIN_FILENO);
    int sdout = dup(STDOUT_FILENO);

    if (error_cases(ac, av) == 84)
        return (84);
    if (isatty(STDIN_FILENO) == 0)
        return echo_process(env, sdin, sdout);
    return (user_process(env, sdin, sdout));
}
