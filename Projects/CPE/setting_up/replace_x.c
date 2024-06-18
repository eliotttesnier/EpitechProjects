/*
** EPITECH PROJECT, 2023
** replace_x.c
** File description:
** replaces the biggest square with x
*/

#include <stdlib.h>
#include "include/header.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "myprintf/include/my.h"

void replace_x(char **arr, s_square *biggest)
{
    int x = biggest->x;
    int y = biggest->y;

    for (int i = x; i < x + biggest->size; i++) {
        for (int j = y; j < y + biggest->size; j++) {
            arr[i][j] = 'x';
        }
    }
}
