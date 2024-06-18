/*
** EPITECH PROJECT, 2024
** open_file
** File description:
** open_file
*/

#include "../includes/header.h"

static void fill_double(char *word, int fd)
{
    size_t size = 0;
    char *line = NULL;

    while (1) {
        write(1, "? ", 2);
        getline(&line, &size, stdin);
        if (line[0] == '\0')
            break;
        if (my_strcmp(line, my_strcat(word, "\n")) == 0)
            break;
        write(fd, line, my_strlen(line));
        line = NULL;
    }
}

int open_double_left(char *word)
{
    int fd = open("/tmp/double_left", O_RDWR | O_TRUNC | O_CREAT,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    fill_double(word, fd);
    close(fd);
    fd = open("/tmp/double_left", O_RDONLY);
    dup2(fd, 66);
    return (66);
}

int open_simple_left(char *path)
{
    int fd = open(path, O_RDONLY);

    if (fd < 3)
        return (my_perror(my_strcat(path,
            ": Is a directory.\n"), -1));
    dup2(fd, 66);
    return (66);
}

int open_double_right(char *path)
{
    int fd = open(path, O_RDWR | O_APPEND | O_CREAT,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd < 3)
        return (my_perror(my_strcat(path,
            ": Is a directory.\n"), -1));
    dup2(fd, 99);
    return (99);
}

int open_simple_right(char *path)
{
    int fd = open(path, O_RDWR | O_TRUNC | O_CREAT,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd < 3)
        return (my_perror(my_strcat(path,
            ": Is a directory.\n"), -1));
    dup2(fd, 99);
    return (99);
}
