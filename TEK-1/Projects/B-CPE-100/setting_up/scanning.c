/*
** EPITECH PROJECT, 2023
** scanning.c
** File description:
** scan the arr and find the biggest square
*/

#include <stdlib.h>
#include "include/header.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "myprintf/include/my.h"

void compares(s_square *actual, s_square *biggest)
{
    if (actual->size > biggest->size) {
        biggest->size = actual->size;
        biggest->x = actual->x;
        biggest->y = actual->y;
    }
}

int scan(char **arr, s_square *actual, int i, int j)
{
    for (int up = actual->x; up <= i; up++) {
        if (arr[up][j] == 'o')
            return (1);
    }
    for (int left = actual->y; left <= j; left++) {
        if (arr[i][left] == 'o')
            return (1);
    }
    return (0);
}

void get_actual_square(char **arr, s_square *actual, int nb_lines)
{
    int size = 0;
    int i = actual->x;
    int j = actual->y;

    while (i < nb_lines && arr[i][j] != '\n') {
        if (scan(arr, actual, i, j) == 1)
            break;
        i++;
        j++;
        size++;
    }
    actual->size = size;
}

int scanning(char **arr, int nb_lines)
{
    s_square actual_square;
    s_square biggest_square = {0, 0, 0};

    for (int i = 0; i < nb_lines && biggest_square.size != nb_lines; i ++) {
        for (int j = 0; arr[i][j] != '\n'
            && biggest_square.size != nb_lines; j++) {
            actual_square.x = i;
            actual_square.y = j;
            get_actual_square(arr, &actual_square, nb_lines);
            compares(&actual_square, &biggest_square);
        }
    }
    replace_x(arr, &biggest_square);
    display_arr(arr, nb_lines);
    return (0);
}
