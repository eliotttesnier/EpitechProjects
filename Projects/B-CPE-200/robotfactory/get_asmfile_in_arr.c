/*
** EPITECH PROJECT, 2024
** get_head.c
** File description:
** get the head of the asm
*/

#include "include/robot_header.h"

char **get_body_in_arr(char *buffer)
{
    char **arr;
    char *header = "\0";
    int nb_quotes = 0;
    int i = 0;

    for (i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"')
            nb_quotes++;
        if (nb_quotes == 4)
            break;
    }
    for (i = i; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n')
            break;
    }
    header = my_strcut(buffer, i, my_strlen(buffer));
    arr = str_to_array(header, "\n");
    format_arr(arr);
    return (arr);
}

char **get_head_in_arr(char *buffer)
{
    char **arr;
    char *header = "\0";
    int nb_quotes = 0;
    int i = 0;

    for (i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"')
            nb_quotes++;
        if (nb_quotes == 4)
            break;
    }
    for (i = i; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n')
            break;
    }
    header = my_strcut(buffer, 0, i);
    arr = str_to_array(header, "\n");
    format_arr(arr);
    return (arr);
}
