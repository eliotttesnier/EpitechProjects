/*
** EPITECH PROJECT, 2023
** display_l
** File description:
** display the -l
*/

#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "../myprintf/include/my.h"

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

void displays_nlinks(char **files, int nb_files, char *p, int a)
{
    struct stat sb;
    int max_len = 0;
    int actual_len = 0;

    for (int i = 0; i < nb_files; i++) {
        get_stats(files[i], p, &sb);
        if (max_len < my_len_nbr(sb.st_nlink))
            max_len = my_len_nbr(sb.st_nlink);
    }
    get_stats(files[a], p, &sb);
    actual_len = my_len_nbr(sb.st_nlink);
    for (int i = 0; i < max_len - actual_len; i++) {
        my_printf(" ");
    }
    my_printf("%i ", sb.st_nlink);
}

static void display_total(char **files, int nb_files, char *p)
{
    struct stat sb;
    int total = 0;

    for (int i = 0; i < nb_files; i++) {
        get_stats(files[i], p, &sb);
        total += sb.st_blocks;
    }
    my_printf("total %i\n", total / 2);
}

void display_l(char **files, int nb_files, char *p)
{
    struct stat sb;

    if (verif(p) == 0)
        display_total(files, nb_files, p);
    for (int i = 0; i < nb_files; i++) {
        get_stats(files[i], p, &sb);
        displays_perms(sb.st_mode);
        displays_nlinks(files, nb_files, p, i);
        displays_name(files, nb_files, p, i);
        displays_group_name(files, nb_files, p, i);
        displays_size(files, nb_files, p, sb.st_size);
        displays_time(&sb);
        my_printf("%s", files[i]);
        if (nb_files != 0)
            my_printf("\n");
    }
}

static void display_normal(char **files, int nb_files, struct mods *m)
{
    for (int i = 0; i < nb_files; i++) {
        my_printf("%s", files[i]);
        if (i < nb_files - 1)
            my_printf(" ");
    }
    my_printf("\n");
}

void call_display(char **f, int nb_f, struct mods *m, char *p)
{
    if (m->l == 1)
        display_l(f, nb_f, p);
    else
        display_normal(f, nb_f, m);
}
