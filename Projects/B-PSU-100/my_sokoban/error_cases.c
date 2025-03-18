/*
** EPITECH PROJECT, 2023
** error_cases.c
** File description:
** error_cases for sokoban
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

static int characters(char *map)
{
    for (int i = 0; map[i] != '\0'; i++) {
        if (map[i] != ' ' && map[i] != '#' && map[i] != 'X'
            && map[i] != 'P' && map[i] != 'O' && map[i] != '\n')
            return (-1);
    }
    return (0);
}

static int nb_player(char *map)
{
    int player = 0;

    for (int i = 0; map[i] != '\0'; i++) {
        if (map[i] == 'P')
            player += 1;
    }
    return (player);
}

static int nb_cases_o(char *map)
{
    int cases = 0;
    int obj = 0;

    for (int i = 0; map[i] != '\0'; i++) {
        if (map[i] == 'X')
            cases += 1;
        if (map[i] == 'O')
            obj += 1;
    }
    if (cases != obj)
        return (-1);
    return (0);
}

int scan_error(char *file)
{
    int buffsiz = size(file);
    int file_desc = open(file, O_RDONLY);
    char *buff = malloc(buffsiz + 5);

    read(file_desc, buff, buffsiz);
    buff[buffsiz] = '\0';
    if (characters(buff) == -1)
        return (-1);
    if (nb_player(buff) != 1)
        return (-1);
    if (nb_cases_o(buff) == -1)
        return (-1);
}

int error_cases(char *file)
{
    struct stat sb;

    if (stat(file, &sb) == -1) {
        write(2, "Error : file doesn't exist\n", 28);
        return (-1);
    }
    if (S_ISDIR(sb.st_mode)) {
        write(2, "Error : Is a directory\n", 24);
        return (-1);
    }
    if (scan_error(file) == -1) {
        write(2, "Error : Map isn't valid\n", 25);
        return (-1);
    }
    return (0);
}
