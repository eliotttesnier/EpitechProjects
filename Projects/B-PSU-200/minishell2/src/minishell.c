/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** minishell
*/

#include "../includes/header.h"

int before_exec(command_t *com, env_t *env)
{
    for (command_t *tmp = com; tmp != NULL; tmp = tmp->redi) {
        if ((is_dir(tmp->bin) == 1 || have_perm(tmp->bin) == 1)
            && tmp->func == NULL)
            return (perm_denied(tmp->bin));
    }
    return (exec_pipe(com, env, com->in));
}

int check_path(command_t *com, env_t *env)
{
    char **paths = NULL;

    for (int i = 0; com->bin[i] != '\0'; i++) {
        if (com->bin[i] == '/')
            return (0);
    }
    for (int i = 0; env->env[i] != NULL; i++) {
        if (my_strccmp("PATH", env->env[i], '=') == 0)
            paths = str_to_array(env->env[i], " \t:=");
    }
    for (int i = 1; paths[i] != NULL; i++) {
        if (access(my_strcat(my_strcat(paths[i], "/"), com->bin), F_OK) == 0) {
            com->bin = my_strcat(my_strcat(paths[i], "/"), com->bin);
            return (0);
        }
    }
    return (command_not_found(com->bin));
}
