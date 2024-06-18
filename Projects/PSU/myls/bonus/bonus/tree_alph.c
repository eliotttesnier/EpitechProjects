/*
** EPITECH PROJECT, 2023
** tree_alph
** File description:
** tree
*/

#include <stdlib.h>
#include "../struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "../myprintf/include/my.h"

int is_tree_a(char **files, int nb_files)
{
    for (int i = 0; i < nb_files - 1; i++) {
        if (compares(files, i, i + 1) == 1)
            return (0);
    }
    return (1);
}

int compares(char **files, int a, int b)
{
    int len_a = pfmy_strlen(files[a]);
    int len_b = pfmy_strlen(files[b]);
    int len_min = len_a;

    if (len_b < len_a)
        len_min = len_b;
    for (int i = 0; i < len_min; i++) {
        if (lower(files[a][i]) > lower(files[b][i]))
            return (1);
        if (lower(files[a][i]) < lower(files[b][i]))
            return (0);
    }
    return (0);
}

int tree_file(char **files, int nb_files)
{
    for (int i = 0; i < nb_files - 1; i++) {
        if (compares(files, i, i + 1) == 1) {
            swap_files(files, i, i + 1);
        }
        if (i == nb_files -2 && is_tree_a(files, nb_files) == 0)
            i = -1;
    }
}
