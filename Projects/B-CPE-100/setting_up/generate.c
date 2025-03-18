/*
** EPITECH PROJECT, 2023
** generate.c
** File description:
** generate the arr
*/

#include <stdlib.h>
#include "include/header.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "myprintf/include/my.h"

int fill(char **arr, int nb_lines, char **av)
{
    int len_pat = pfmy_strlen(av[2]);
    int a = 0;
    int j = 0;
    int x = 0;

    for (int i = 0; i < nb_lines * nb_lines; i++) {
        if (a == len_pat)
            a = 0;
        if (j == nb_lines) {
            arr[x][j] = '\n';
            j = 0;
            x += 1;
        }
        arr[x][j] = av[2][a];
        a += 1;
        j += 1;
    }
    arr[x][j] = '\n';
}

int generate(char **av)
{
    int nb_lines = pfmy_getnbr(av[1], 0);
    char **arr = malloc(sizeof(char *) * nb_lines);

    for (int i = 0; i < nb_lines; i++) {
        arr[i] = malloc(nb_lines + 10);
    }
    fill(arr, nb_lines, av);
    scanning(arr, nb_lines);
    free(arr);
    return (0);
}
