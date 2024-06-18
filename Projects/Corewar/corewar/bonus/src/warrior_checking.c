/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** warrior_checking
*/

#include "corewar_header.h"

bool check_path(char *path)
{
    int fd = open(path, O_RDONLY);
    int len = my_strlen(path);

    if (fd == -1)
        return (false);
    close(fd);
    if (len <= 4)
        return (false);
    if (path[len - 1] != 'r' || path[len - 2] != 'o' ||
        path[len - 3] != 'c' || path[len - 4] != '.')
        return (false);
    return (true);
}

int check_for_warriors(argument_t *args)
{
    args_t *tmp = args->args;
    bool ret = true;

    args->nb_programs = 0;
    while (tmp != NULL) {
        ret = true;
        if (tmp->path == true) {
            args->nb_programs++;
            ret = check_path(tmp->arg);
        }
        if (ret == false)
            return (my_perror("INIT: header error\n", 84));
        tmp = tmp->next;
    }
    if (args->nb_programs < 2)
        return (my_perror("INIT: Too few warrior\n", 84));
    if (args->nb_programs > 4)
        return (my_perror("INIT: Too many warrior\n", 84));
    return (0);
}
