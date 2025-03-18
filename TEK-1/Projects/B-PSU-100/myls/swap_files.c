/*
** EPITECH PROJECT, 2023
** swap_files
** File description:
** swap_files
*/

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

int swap_files(char **files, int a, int b)
{
    int len_a = pfmy_strlen(files[a]);
    int len_b = pfmy_strlen(files[b]);
    int lenmax = len_a;
    char temp = 'a';

    if (pfmy_strlen(files[b]) > lenmax)
        lenmax = pfmy_strlen(files[b]);
    for (int j = 0; j < lenmax; j++) {
        temp = files[a][j];
        files[a][j] = files[b][j];
        files[b][j] = temp;
    }
    files[a][len_b] = '\0';
    files[b][len_a] = '\0';
    return (0);
}
