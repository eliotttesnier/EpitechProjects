/*
** EPITECH PROJECT, 2023
** generate_errors.c
** File description:
** check for error cases with the generate method
*/

#include <stdlib.h>
#include "../include/header.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../myprintf/include/my.h"

int error2(char **av)
{
    for (int i = 0; i < pfmy_strlen(av[1]); i++) {
        if (av[1][i] > '9' || av[1][i] < '0') {
            write(2,
            "Error : first argument must be an integer greater than 0\n", 58);
            exit(84);
        }
    }
}

int generate_errors(char **av)
{
    int nb = pfmy_getnbr(av[1], 0);

    if (nb <= 0) {
        write(2,
        "Error : first argument must be an integer greater than 0\n", 58);
        return (-1);
    }
    error2(av);
    if (pfmy_strlen(av[2]) < 1) {
        write(2, "Error : Pattern can't be empty\n", 31);
        return (-1);
    }
    for (int i = 0; i < pfmy_strlen(av[2]); i++) {
        if (av[2][i] != '.' && av[2][i] != 'o') {
            write(2,
            "Error : pattern must only be composed of '.' and 'o'\n", 54);
            return (-1);
        }
    }
    return (0);
}
