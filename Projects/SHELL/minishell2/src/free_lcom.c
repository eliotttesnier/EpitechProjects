/*
** EPITECH PROJECT, 2024
** reset_fd
** File description:
** reset_fd
*/

#include "../includes/header.h"

void free_redirections(command_t *redi)
{
    if (redi == NULL)
        return;
    free_redirections(redi->next);
    free(redi->bin);
    free(redi->args);
    free(redi);
}

command_t *free_lcom(command_t *lcom, int sdin, int sdout)
{
    command_t *next;

    if (lcom == NULL)
        return (NULL);
    next = lcom->next;
    if (lcom->fd != 0)
        close(lcom->fd);
    if (lcom->in != 0)
        close(lcom->in);
    free_redirections(lcom->redi);
    free(lcom->bin);
    for (int i = 0; lcom->args[i] != NULL; i++) {
        free(lcom->args[i]);
    }
    free(lcom);
    dup2(sdin, STDIN_FILENO);
    dup2(sdout, STDOUT_FILENO);
    return (next);
}
