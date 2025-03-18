/*
** EPITECH PROJECT, 2024
** error_cases
** File description:
** error_cases
*/

#include "stumper.h"

static int my_perror(char *str, int ret)
{
    write(2, str, strlen(str));
    return (ret);
}

static int is_dir(char *path)
{
    struct stat sb;

    stat(path, &sb);
    return (S_ISDIR(sb.st_mode));
}

int get_size(char *path)
{
    struct stat sb;

    stat(path, &sb);
    return (sb.st_size);
}

int check_file(char *path)
{
    int fd = open(path, O_RDONLY);

    if (fd == -1)
        return (my_perror(strcat(path, " : Unkown file.\n"), -1));
    if (is_dir(path) == 1)
        return (my_perror(strcat(path, " : is a directory.\n"), -1));
    close(fd);
    return (0);
}

int check_content(char *path)
{
    int fd = open(path, O_RDONLY);
    int size = get_size(path);
    char *buf = malloc(sizeof(char) * size);
    bool empty = true;

    if (buf == NULL)
        return (my_perror("Malloc fail", -1));
    read(fd, buf, size);
    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] != '\n' && buf[i] != ' ' && buf[i] != '\t')
            empty = false;
    }
    if (too_many_words(buf) == -1)
        return (my_perror("Two many words on single line.\n", -1));
    free(buf);
    close(fd);
    return (empty == false ? 0 : my_perror("No words found.\n", -1));
}

int only_numbers(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (IS_NUMBER(str[i]) != 1)
            return (my_perror("Invalid number for tries.\n", -1));
    }
    if (atoi(str) == 0)
        return (my_perror("Invalid number for tries.\n", -1));
    return (0);
}

int error_cases(int ac, char **av)
{
    if (ac <= 1 || ac > 3)
        return (my_perror("Invalid arguments number.\n", -1));
    if (check_file(av[1]) == -1)
        return (-1);
    if (check_content(av[1]) == -1)
        return (-1);
    if (ac == 2)
        return (0);
    return ((only_numbers(av[2]) == 0 ? 0 : -1));
}
