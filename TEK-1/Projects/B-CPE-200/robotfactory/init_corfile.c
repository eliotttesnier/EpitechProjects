/*
** EPITECH PROJECT, 2024
** init_corfile.c
** File description:
** Init the cor file
*/

#include "include/robot_header.h"

char *cor_format_name(char *file_name)
{
    char *corfile;
    int ind = -1;

    for (int i = 0; file_name[i] != '\0'; i++) {
        if (file_name[i] == '/')
            ind = i;
    }
    file_name[my_strlen(file_name) - 2] = '\0';
    corfile = my_strcut(file_name, ind + 1, my_strlen(file_name));
    corfile = my_strcat(corfile, ".cor");
    return (corfile);
}

int create_cor_file(char *file_name)
{
    char *corfile = cor_format_name(file_name);
    int fd = open(corfile, O_RDWR | O_TRUNC | O_CREAT,
        S_IRWXG | S_IRWXO | S_IRWXU);

    free(corfile);
    if (fd == -1)
        return (my_perror("Failed to create the .cor file.\n", -1));
    return (fd);
}
