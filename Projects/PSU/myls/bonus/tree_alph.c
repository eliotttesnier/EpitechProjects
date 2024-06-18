/*
** EPITECH PROJECT, 2023
** tree_alph
** File description:
** tree
*/

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

int tree_file(char **files, int nb_files)
{
    for (int i = 0; i < nb_files - 1; i++) {
        if (compares(files, i, i + 1) == 1) {
            swap_files(files, i, i + 1);
            i = -1;
        }
    }
}
