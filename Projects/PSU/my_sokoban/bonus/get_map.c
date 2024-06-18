/*
** EPITECH PROJECT, 2023
** get_map.c
** File description:
** put the map in an array
*/

#include "header.h"
#include "myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

static int size(char *file)
{
    struct stat sb;

    lstat(file, &sb);
    return (sb.st_size);
}

static int calc_lines(char *buff)
{
    int lines = 0;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == '\n')
            lines += 1;
    }
    return (lines);
}

static int max_len(char *buff)
{
    int actual_len = 0;
    int maxlen = 0;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == '\n' && actual_len > maxlen)
            maxlen = actual_len;
        if (buff[i] == '\n')
            actual_len = -1;
        actual_len += 1;
    }
    return (maxlen);
}

char **fill_arr(char **map, char *buff, int *nbline, int *maxlen)
{
    int nb_lines = calc_lines(buff);
    int len_max = max_len(buff) + 1;
    int x = 0;
    int y = 0;

    *nbline = nb_lines;
    map = malloc(sizeof(char *) * nb_lines);
    for (int i = 0; i < nb_lines; i ++) {
        map[i] = malloc(len_max);
    }
    for (int i = 0; buff[i] != '\0'; i++) {
        map[x][y] = buff[i];
        y += 1;
        if (buff[i] == '\n') {
            x += 1;
            y = 0;
        }
    }
    *maxlen = len_max;
    return (map);
}

char **get_map(char **map, char *file, int *nb_lines, int *maxlen)
{
    int buffsiz = size(file);
    int file_desc = open(file, O_RDONLY);
    char *buff = malloc(buffsiz + 5);

    read(file_desc, buff, buffsiz);
    buff[buffsiz] = '\0';
    map = fill_arr(map, buff, nb_lines, maxlen);
    return (map);
}
