/*
** EPITECH PROJECT, 2024
** exec_simple_com
** File description:
** exec simple com
*/

#include "../includes/header.h"

int exec_com(command_t *com, env_t *env)
{
    int wstatus = 0;
    pid_t child;

    if (com->func != NULL)
        return (com->func(com->args, env));
    child = fork();
    if (child == 0) {
        execve(com->bin, com->args, env->env);
        failed_exec(com->bin, errno);
        exit(EXIT_FAILURE);
    }
    waitpid(child, &wstatus, WUNTRACED | WCONTINUED);
    if (wstatus == 139 || wstatus == 11)
        return (crash(wstatus));
    return (WEXITSTATUS(wstatus));
}
