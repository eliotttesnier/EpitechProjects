/*
** EPITECH PROJECT, 2023
** get_stats
** File description:
** get the stats
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

void get_stats(char *file, char *path, struct stat *sb)
{
    char *str;
    int a = 0;

    str = malloc(pfmy_strlen(path) * pfmy_strlen(file) + 1);
    for (int i = 0; i < pfmy_strlen(path); i++) {
        str[a] = path[i];
        a += 1;
    }
    if (path[pfmy_strlen(path) - 1] != '/' && pfmy_strlen(path) != 0) {
        str[a] = '/';
        a += 1;
    }
    for (int i = 0; i < pfmy_strlen(file); i++) {
        str[a] = file[i];
        a += 1;
    }
    str[a] = '\0';
    lstat(str, sb);
    if (verif(path) == 1)
        lstat(path, sb);
}
