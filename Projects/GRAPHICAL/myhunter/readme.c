/*
** EPITECH PROJECT, 2023
** readme.c
** File description:
** displays the rules
*/

#include <SFML/Audio.h>
#include "header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int display_readme(int ac, char **av)
{
    int buffsiz = 4096;
    int file_desc = open("texts_files/rules.txt", O_RDONLY);
    char buff[buffsiz + 1];
    int offset = 0;
    int len = read(file_desc, buff + offset, buffsiz - offset);

    while (len > 0) {
        offset += len;
        len = read(file_desc, buff + offset, buffsiz - offset);
    }
    buff[offset] = '\0';
    for (int i = 0; buff[i] != '\0'; i++) {
        write(1, &buff[i], 1);
    }
    close(file_desc);
    return (0);
}

int readme(int ac, char **av)
{
    if (my_strlen(av[1]) != 2)
        return (84);
    if (av[1][0] != '-')
        return (84);
    if (av[1][1] != 'h')
        return (84);
    display_readme(ac, av);
}
