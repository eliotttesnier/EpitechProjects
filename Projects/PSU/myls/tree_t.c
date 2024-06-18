/*
** EPITECH PROJECT, 2023
** tree_t
** File description:
** trees the tab
*/

#include <time.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

void reverse_file(char **files, int nb_files)
{
    int middle = nb_files / 2 + 1;

    if (nb_files == 2) {
        swap_files(files, 0, 1);
        return;
    }
    for (int i = 0; i < middle; i++){
        swap_files(files, i, nb_files - 1 - i);
    }
}

int compares_tflag(char **files, int a, int b, char *path)
{
    struct stat sb;
    struct stat sb2;
    long int first = 0;
    long int second = 0;

    get_stats(files[a], path, &sb);
    first = sb.st_mtime;
    get_stats(files[b], path, &sb2);
    second = sb2.st_mtime;
    if (first < second)
        return (1);
    return (0);
}

int is_tree(char **files, int nb_files, char *path)
{
    struct stat sb;
    struct stat sb2;

    for (int i = 0; i < nb_files - 1; i++) {
        get_stats(files[i], path, &sb);
        get_stats(files[i + 1], path, &sb2);
        if (sb.st_mtime < sb2.st_mtime) {
            return (0);
        }
    }
    return (1);
}

void tree_tflag(char **files, int nb_files, char *path)
{
    for (int i = 0; i < nb_files - 1; i++) {
        if (compares_tflag(files, i, i + 1, path) == 1)
            swap_files(files, i, i + 1);
        if (i == nb_files - 2 && is_tree(files, nb_files, path) == 0)
            i = -1;
    }
}
