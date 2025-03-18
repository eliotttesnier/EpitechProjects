/*
** EPITECH PROJECT, 2024
** perm_dir.c
** File description:
** perm_dir
*/

#include "../includes/header.h"

int have_perm(char *path)
{
    if (access(path, F_OK) != 0)
        return (0);
    if (access(path, X_OK) != 0)
        return (1);
    return (0);
}

int is_dir(char *path)
{
    struct stat sb;

    if (access(path, F_OK) != 0)
        return (0);
    stat(path, &sb);
    return (S_ISDIR(sb.st_mode));
}
