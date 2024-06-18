/*
** EPITECH PROJECT, 2023
** get_from_line.c
** File description:
** create the array from a file
*/

#include <stdlib.h>
#include "include/header.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "myprintf/include/my.h"

int size(char *file)
{
    struct stat sb;

    stat(file, &sb);
    return (sb.st_size);
}

static void filling(char **arr, char *buff, int nb_lines)
{
    int i = 0;
    int x = 0;
    int y = 0;
    int len_line = pfmy_strlen(buff) / nb_lines;

    for (int a = 0; a < nb_lines; a++) {
        arr[a] = malloc(len_line + 10);
    }
    for (i = 1; buff[i - 1] != '\n'; i++) {
    }
    for (i = i; buff[i] != '\0'; i++) {
        arr[x][y] = buff[i];
        y += 1;
        if (buff[i] == '\n') {
            arr[x][y] = '\0';
            x += 1;
            y = 0;
        }
    }
}

void fill_arr(char **arr, int nb_lines, char *file)
{
    int buffsiz = size(file);
    int file_desc = open(file, O_RDONLY);
    char *buff = malloc(buffsiz + 5);
    int offset = 0;
    int len = read(file_desc, buff + offset, buffsiz - offset);

    while (len > 0) {
        offset += len;
        len = read(file_desc, buff + offset, buffsiz - offset);
    }
    buff[offset] = '\0';
    filling(arr, buff, nb_lines);
    close(file_desc);
    free(buff);
}

int get_nb_lines(char *file)
{
    int buffsiz = size(file);
    int file_desc = open(file, O_RDONLY);
    char *buff = malloc(buffsiz + 5);
    int offset = 0;
    int len = read(file_desc, buff + offset, buffsiz - offset);
    char number[20];

    while (len > 0) {
        offset += len;
        len = read(file_desc, buff + offset, buffsiz - offset);
    }
    buff[offset] = '\0';
    for (int i = 0; buff[i] != '\n' && buff[i] != '\0'; i++) {
        number[i] = buff[i];
        number[i + 1] = '\0';
    }
    close(file_desc);
    free(buff);
    return (pfmy_getnbr(number, 0));
}

int get_from_file(char **av)
{
    int nb_lines = get_nb_lines(av[1]);
    char **arr = malloc(sizeof(char *) * nb_lines);

    fill_arr(arr, nb_lines, av[1]);
    scanning(arr, nb_lines);
    free(arr);
    return (0);
}
