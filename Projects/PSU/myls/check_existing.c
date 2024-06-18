/*
** EPITECH PROJECT, 2023
** check_existing
** File description:
** check if every file/folder exist
*/

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

int check_existing(char *check)
{
    struct stat sb;

    if (lstat(check, &sb) == -1) {
        my_printf("ls: cannot access '%s':", check);
        my_printf(" No such file or directory\n");
        return (-1);
    }
    return (0);
}

int non_existing_secu(char **arr, int nb_paths, int *i)
{
    while (check_existing(arr[*i]) == -1) {
        *i += 1;
        if (*i >= nb_paths)
            return (-1);
    }
    return (0);
}
