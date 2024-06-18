/*
** EPITECH PROJECT, 2023
** comparison
** File description:
** compares 2 str
*/

#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

int compares(char **files, int a, int b)
{
    int len_a = pfmy_strlen(files[a]);
    int len_b = pfmy_strlen(files[b]);
    int len_min = len_a;

    if (len_b < len_a)
        len_min = len_b;
    for (int i = 0; i < len_min; i++) {
        if (lower(files[a][i]) > lower(files[b][i]))
            return (1);
        if (lower(files[a][i]) < lower(files[b][i]))
            return (0);
    }
    return (0);
}