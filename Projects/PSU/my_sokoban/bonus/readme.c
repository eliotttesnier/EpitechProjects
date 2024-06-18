/*
** EPITECH PROJECT, 2023
** .c
** File description:
** display a str in full screen
*/

#include "header.h"
#include "myprintf/include/my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

int readme(void)
{
    int buffsiz = 4096;
    int file_desc = open("readme.txt", O_RDONLY);
    char *buff = malloc(buffsiz + 5);

    read(file_desc, buff, buffsiz);
    buff[buffsiz] = '\0';
    my_printf("%s", buff);
    return (0);
}
