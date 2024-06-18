/*
** EPITECH PROJECT, 2023
** myls
** File description:
** reproduces myls
*/

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

int display_d(char **arr, struct mods *modifiers, int nb_paths, int max)
{
    struct stat sb;

    for (int i = 0; i < nb_paths; i++)
        if (check_existing(arr[i]) == -1)
            return (84);
    if (modifiers->t == 1)
        tree_tflag(arr, nb_paths, "");
    if (modifiers->r == 1)
        reverse_file(arr, nb_paths);
    call_display(arr, nb_paths, modifiers, "");
    return (0);
}

int display_path(char *path, struct mods *modifiers)
{
    int nb_files = call_cal_file(path, modifiers);
    int len_max_file = call_file_len(path, modifiers);
    char **files = malloc(sizeof(char *) * nb_files);

    for (int i = 0; i < nb_files; i++) {
        files[i] = malloc(sizeof(char) * len_max_file + 1);
    }
    call_fill_file(path, files, nb_files, modifiers);
    if (modifiers->t == 1)
        tree_tflag(files, nb_files, path);
    if (modifiers->r == 1)
        reverse_file(files, nb_files);
    call_display(files, nb_files, modifiers, path);
    free(files);
}

static int verif(char *path)
{
    if (pfmy_strlen(path) == 1 && path[0] == '.')
        return (0);
    for (int i = 0; i < pfmy_strlen(path); i++) {
        if (path[i] == '/')
            return (0);
    }
    return (1);
}

static int nb_path(int nb_path)
{
    if (nb_path == 0)
        return (1);
    return (0);
}

int myls(int ac, char **av, struct mods *modifiers)
{
    int nb_paths = cal_paths(ac, av);
    int len_max_path = cal_len_max(ac, av);
    char **arr = malloc(sizeof(char *) * (nb_paths + 1));

    for (int i = 0; i < nb_paths; i++) {
        arr[i] = malloc(sizeof(char) * len_max_path);
    }
    fill_arr(av, arr, nb_paths);
    nb_paths = nb_paths + nb_path(nb_paths);
    if (modifiers->d == 1)
        return display_d(arr, modifiers, nb_paths, len_max_path);
    for (int i = 0; i < nb_paths; i++) {
        if (non_existing_secu(arr, nb_paths, &i) == -1)
            return (0);
        if (nb_paths > 1 && verif(arr[i]) == 0)
            my_printf("%s:\n", arr[i]);
        display_path(arr[i], modifiers);
        my_printf( (i != nb_paths - 1) ? "\n" : "");
    }
    free(arr);
}

int main(int ac, char **av)
{
    struct stat sb;
    struct mods modifiers;
    int ret = 0;

    fill_struct(&modifiers, av, ac);
    myls(ac, av, &modifiers);
    return (0);
}
