/*
** EPITECH PROJECT, 2024
** error_cases
** File description:
** error_cases
*/

#include "../includes/header.h"

int error_cases(int ac, char **av)
{
    if (ac != 1)
        return (84);
    if (av[1] != NULL)
        return (84);
    return (0);
}
