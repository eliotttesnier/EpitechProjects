/*
** EPITECH PROJECT, 2023
** displays_name
** File description:
** displays the name
*/

#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "../myprintf/include/my.h"

void displays_group_name(char **files, int nb_files, char *p, int a)
{
    struct stat sb;
    struct group *g;
    int max_len = 0;
    int actual_len = 0;

    for (int i = 0; i < nb_files; i++) {
        get_stats(files[i], p, &sb);
        g = getgrgid(sb.st_gid);
        if (max_len < pfmy_strlen(g->gr_name))
            max_len = pfmy_strlen(g->gr_name);
    }
    get_stats(files[a], p, &sb);
    g = getgrgid(sb.st_gid);
    actual_len = pfmy_strlen(g->gr_name);
    my_printf("%s ", g->gr_name);
    for (int i = 0; i < max_len - actual_len; i++) {
        my_printf(" ");
    }
}

void displays_name(char **files, int nb_files, char *p, int a)
{
    struct stat sb;
    struct passwd *g;
    int max_len = 0;
    int actual_len = 0;

    for (int i = 0; i < nb_files; i++) {
        get_stats(files[i], p, &sb);
        g = getpwuid(sb.st_uid);
        if (max_len < pfmy_strlen(g->pw_name))
            max_len = pfmy_strlen(g->pw_name);
    }
    get_stats(files[a], p, &sb);
    g = getpwuid(sb.st_uid);
    actual_len = pfmy_strlen(g->pw_name);
    my_printf("%s ", g->pw_name);
    for (int i = 0; i < max_len - actual_len; i++) {
        my_printf(" ");
    }
}
