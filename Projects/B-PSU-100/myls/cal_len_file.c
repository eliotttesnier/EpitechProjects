/*
** EPITECH PROJECT, 2023
** cal_len_file
** File description:
** calcul the max len
*/

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

int file_len_max(char *str)
{
    int max = 0;
    struct dirent *pDirent;
    DIR *pDir;

    pDir = opendir(str);
    if (pDir == NULL)
        return (pfmy_strlen(str));
    pDirent = readdir(pDir);
    while (pDirent != NULL) {
        if (pDirent->d_name[0] != '.'
        && pfmy_strlen(pDirent->d_name) > max)
            max = pfmy_strlen(pDirent->d_name);
        pDirent = readdir(pDir);
    }
    closedir(pDir);
    return (max);
}

int file_len_max_a(char *str)
{
    int max = 0;
    struct dirent *pDirent;
    DIR *pDir;

    pDir = opendir(str);
    if (pDir == NULL)
        return (pfmy_strlen(str));
    pDirent = readdir(pDir);
    while (pDirent != NULL) {
        if (pfmy_strlen(pDirent->d_name) > max)
            max = pfmy_strlen(pDirent->d_name);
        pDirent = readdir(pDir);
    }
    closedir(pDir);
    return (max);
}

int call_file_len(char *str, struct mods *modifiers)
{
    if (modifiers->a == 1)
        return (file_len_max_a(str));
    return (file_len_max(str));
}
