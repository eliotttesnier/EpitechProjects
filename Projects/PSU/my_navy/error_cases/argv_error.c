/*
** EPITECH PROJECT, 2024
** argv_error
** File description:
** error cases for argv
*/

#include "../include/navy_header.h"

int verif_filename(char *file)
{
    int fd = open(file, O_RDONLY);

    if (fd == -1)
        return (84);
    return (0);
}

int verif_pid(char *pid)
{
    if (pid[0] == '\0')
        return (84);
    for (int i = 0; i < my_strlen(pid); i++) {
        if (pid[i] > '9' || pid[i] < '0')
            return (84);
    }
    return (0);
}

int argv_error(int ac, char **av)
{
    if (ac == 2)
        return (verif_filename(av[1]));
    if (ac == 3) {
        if (verif_pid(av[1]) == 84)
            return (84);
        return (verif_filename(av[2]));
    }
    return (84);
}
