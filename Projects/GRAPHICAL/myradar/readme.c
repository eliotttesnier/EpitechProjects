/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main file
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"
#include "fcntl.h"
#include <unistd.h>

int readme(int ac, char **av)
{
    int file_desc = open("readme.txt", O_RDONLY);
    int size = get_size("readme.txt");
    char *buff = malloc(size + 1);

    read(file_desc, buff, size);
    buff[size] = '\0';
    my_printf("%s", buff);
    return (0);
}
