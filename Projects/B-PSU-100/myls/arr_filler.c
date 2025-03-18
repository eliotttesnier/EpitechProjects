/*
** EPITECH PROJECT, 2023
** arr_filler
** File description:
** used to fill the arr
*/

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

void fill_arr(char **av, char **arr, int nb_paths)
{
    int i = 1;
    int j = 0;
    int a = 0;

    while (j < nb_paths) {
        while (av[i][0] == '-') {
            i += 1;
        }
        arr[j][a] = av[i][a];
        a += 1;
        if (a >= pfmy_strlen(av[i])) {
            a = 0;
            i += 1;
            j += 1;
        }
    }
    if (nb_paths == 0) {
        arr[0] = malloc(sizeof(char));
        arr[0][0] = '.';
    }
}

int cal_len_max(int ac, char **av)
{
    int max = 0;

    for (int i = 1; i < ac; i++) {
        if (av[i][0] != '-' && pfmy_strlen(av[i]) > max)
            max = pfmy_strlen(av[i]);
    }
    return (max);
}

int cal_paths(int ac, char **av)
{
    int nb_paths = 0;

    for (int i = 1; i < ac; i++) {
        if (av[i][0] != '-')
            nb_paths += 1;
    }
    return (nb_paths);
}
