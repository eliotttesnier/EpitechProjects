/*
** EPITECH PROJECT, 2024
** execution.c
** File description:
** execution.c
*/

#include "../includes/header.h"

static void redirect_fd(int old, int new)
{
    if (old == new)
        return;
    dup2(old, new);
    close(old);
}

int last_command(command_t *com, env_t *env, int in_fd)
{
    if (com->fd != 0)
        dup2(com->fd, STDOUT_FILENO);
    redirect_fd(in_fd, STDIN_FILENO);
    return (exec_com(com, env));
}

int exec_pipe(command_t *com, env_t *env, int in_fd)
{
    pid_t cpid = 0;
    int pipefd[2];
    int wstatus = 0;

    if (com->redi == NULL)
        return (last_command(com, env, in_fd));
    pipe(pipefd);
    cpid = fork();
    if (cpid == 0) {
        close(pipefd[0]);
        redirect_fd(in_fd, STDIN_FILENO);
        redirect_fd(pipefd[1], STDOUT_FILENO);
        exit(exec_com(com, env));
    }
    close(pipefd[1]);
    close(in_fd);
    exec_pipe(com->redi, env, pipefd[0]);
    waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
    return (WEXITSTATUS(wstatus));
}
