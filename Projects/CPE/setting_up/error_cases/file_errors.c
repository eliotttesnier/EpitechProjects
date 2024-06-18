/*
** EPITECH PROJECT, 2023
** file_errors.c
** File description:
** check for error cases with the file method
*/

#include <stdlib.h>
#include "../include/header.h"
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../myprintf/include/my.h"

static int first_line(char *buff)
{
    int i = 0;

    for (i = 0; buff[i] != '\n' && buff[i] != '\0'; i++) {
        if (buff[i] < '0' || buff[i] > '9') {
            write(2, "Error : wrong format\n", 22);
            return (-1);
        }
    }
    return (i);
}

static int characters(char *buff, int beg)
{
    for (int i = beg; buff[i] != '\0'; i++) {
        if (buff[i] != '.' && buff[i] != 'o' && buff[i] != '\n') {
            write(2, "Error : wrong format\n", 22);
            return (-1);
        }
    }
    return (0);
}

static int same_lenght(char *buff, int beg)
{
    int len = 0;
    int actual_len = 0;

    for (int i = beg + 1; buff[i] != '\n'; i++) {
        len += 1;
    }
    for (int i = beg + 1; buff[i] != '\0'; i++) {
        if (buff[i] == '\n' && actual_len != len) {
            write(2, "Error : wrong format\n", 22);
            return (-1);
        }
        if (buff[i] == '\n')
            actual_len = -1;
        actual_len += 1;
    }
    return (0);
}

static int nb_lines(char *buff, char *file, int beg)
{
    int nb_line = get_nb_lines(file);
    int real_nbline = 0;

    if (nb_line == 0)
        return (-1);
    for (int i = beg + 1; buff[i] != '\0'; i++) {
        if (buff[i] == '\n')
            real_nbline += 1;
    }
    if (real_nbline != nb_line) {
        write(2, "Error : wrong format\n", 22);
        return (-1);
    }
    return (0);
}

int tests_with_file(char *buff, char **av)
{
    int i = 0;
    int beg = 0;

    beg = first_line(buff);
    if (nb_lines(buff, av[1], beg) == -1)
        return (-1);
    if (beg == -1)
        return (-1);
    if (characters(buff, beg) == -1)
        return (-1);
    if (same_lenght(buff, beg) == -1)
        return (-1);
    if (buff[beg + 1] == '\0' || buff[beg + 1] == '\n') {
        write(2, "Error : wrong format\n", 22);
        return (-1);
    }
    return (0);
}

int second_part(char **av)
{
    int buffsiz = size(av[1]);
    int file_desc = open(av[1], O_RDONLY);
    char *buff = malloc(buffsiz + 5);
    int offset = 0;
    int len = read(file_desc, buff + offset, buffsiz - offset);

    while (len > 0) {
        offset += len;
        len = read(file_desc, buff + offset, buffsiz - offset);
    }
    buff[offset] = '\0';
    close(file_desc);
    if (tests_with_file(buff, av) == -1)
        return (-1);
    free(buff);
    return (0);
}

int file_errors(char **av)
{
    struct stat sb;

    if (stat(av[1], &sb) == -1) {
        write(2, "Error : file doesn't exist\n", 28);
        return (-1);
    }
    if (S_ISDIR(sb.st_mode)) {
        write(2, "Error : Is a directory\n", 24);
        return (-1);
    }
    if (second_part(av) == -1)
        return (-1);
    return (0);
}
