/*
** EPITECH PROJECT, 2023
** display_arr.c
** File description:
** displays the final arr
*/

#include <stdlib.h>
#include "include/header.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "myprintf/include/my.h"

int display_arr(char **arr, int nb_lines)
{
    char *to_print = malloc(nb_lines * pfmy_strlen(arr[0]) + 10);
    int a = 0;
    int len = pfmy_strlen(arr[0]);

    for (int i = 0; i < nb_lines; i++) {
        write(1, arr[i], len);
    }
}
