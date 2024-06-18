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

int find_func(char **com, env_t *env)
{
    for (int i = 0; commands[i].func != NULL; i++) {
        if (my_strcmp(com[0], commands[i].name) == 0)
            return (commands[i].func(com, env));
    }
    if (com[0][0] == '\0')
        return (0);
    return (execute_command(com, env));
}

int user_process(env_t *env)
{
    size_t size = 0;
    int ind = 0;
    char *com = NULL;

    while (1) {
        write(1, "$> ", 3);
        getline(&com, &size, stdin);
        for (ind = 0; com[ind] != '\n'; ind++);
        com[ind] = '\0';
        find_func(str_to_array_space(com), env);
        com = NULL;
    }
    return (0);
}

int echo_process(env_t *env)
{
    size_t size = 0;
    int ind = 0;
    char *com = NULL;
    int ret = 0;

    while (1) {
        getline(&com, &size, stdin);
        if (com[0] == '\0')
            break;
        for (ind = 0; com[ind] != '\n'; ind++);
        com[ind] = '\0';
        ret = find_func(str_to_array_space(com), env);
        if (ret != 0)
            break;
        com = NULL;
    }
    return (ret);
}

int minishell(int ac, char **av, env_t *env)
{
    if (error_cases(ac, av) == 84)
        return (84);
    if (isatty(STDIN_FILENO) == 0)
        return echo_process(env);
    return (user_process(env));
}
