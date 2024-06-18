/*
** EPITECH PROJECT, 2024
** open_asm.c
** File description:
** open the asm file
*/

#include "include/robot_header.h"

int open_asm_file(char *file_name)
{
    int fd = open(file_name, O_RDONLY);

    if (fd == -1)
        return (my_perror("No such file or directory.\n", -1));
    return (fd);
}
