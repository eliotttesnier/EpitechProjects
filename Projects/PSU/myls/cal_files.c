/*
** EPITECH PROJECT, 2023
** cal_files
** File description:
** calcul the nb of files
*/

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

int cal_file(char *str)
{
    int nb_file = 0;
    struct dirent *pDirent;
    DIR *pDir;

    pDir = opendir(str);
    if (pDir == NULL)
        return (1);
    pDirent = readdir(pDir);
    while (pDirent != NULL) {
        if (pDirent->d_name[0] != '.')
            nb_file += 1;
        pDirent = readdir(pDir);
    }
    closedir(pDir);
    return (nb_file);
}

int cal_file_a(char *str)
{
    int nb_file = 0;
    struct dirent *pDirent;
    DIR *pDir;

    pDir = opendir(str);
    if (pDir == NULL)
        return (1);
    pDirent = readdir(pDir);
    while (pDirent != NULL) {
        pDirent = readdir(pDir);
        nb_file += 1;
    }
    closedir(pDir);
    return (nb_file);
}

int call_cal_file(char *str, struct mods *modifiers)
{
    if (modifiers->a == 1)
        return (cal_file_a(str));
    return (cal_file(str));
}
