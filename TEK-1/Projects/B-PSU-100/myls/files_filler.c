/*
** EPITECH PROJECT, 2023
** files_filler
** File description:
** used to fill the files
*/

#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

static int fill_file_file(char *path, char **file)
{
    for (int i = 0; i < pfmy_strlen(path); i++) {
        file[0][i] = path[i];
        file[0][i + 1] = '\0';
    }
    return (0);
}

int fill_file(char *path, char **file, int nb_files)
{
    struct dirent *pDirent;
    DIR *pDir;

    pDir = opendir(path);
    if (pDir == NULL)
        return (fill_file_file(path, file));
    for (int i = 0; i < nb_files; i++) {
        pDirent = readdir(pDir);
        while (pDirent != NULL && pDirent->d_name[0] == '.') {
            pDirent = readdir(pDir);
        }
        if (pDirent == NULL)
            break;
        for (int j = 0; j < pfmy_strlen(pDirent->d_name); j++) {
            file[i][j] = pDirent->d_name[j];
            file[i][j + 1] = '\0';
        }
    }
    closedir(pDir);
}

int fill_file_a(char *path, char **file, int nb_files)
{
    struct dirent *pDirent;
    DIR *pDir;

    pDir = opendir(path);
    if (pDir == NULL)
        return (fill_file_file(path, file));
    for (int i = 0; i < nb_files; i++) {
        pDirent = readdir(pDir);
        if (pDirent == NULL)
            break;
        for (int j = 0; j < pfmy_strlen(pDirent->d_name); j++) {
            file[i][j] = pDirent->d_name[j];
            file[i][j + 1] = '\0';
        }
    }
    closedir(pDir);
}

void call_fill_file(char *p, char **f, int nb_f, struct mods *mods)
{
    if (mods->a == 1) {
        fill_file_a(p, f, nb_f);
        return;
    }
    fill_file(p, f, nb_f);
}
