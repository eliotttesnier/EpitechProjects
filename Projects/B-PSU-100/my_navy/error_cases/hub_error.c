/*
** EPITECH PROJECT, 2024
** hub_error
** File description:
** hub for error cases
*/

#include "../include/navy_header.h"

int hub_error(int ac, char **av)
{
    if (argv_error(ac, av) == 84)
        return (84);
    if (check_file(av[ac - 1]) == 84)
        return (84);
    return (0);
}
