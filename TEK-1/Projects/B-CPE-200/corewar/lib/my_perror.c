/*
** EPITECH PROJECT, 2024
** my_perror.c
** File description:
** my_perror
*/

#include "../include/corewar_header.h"

int my_perror(char *msg, int return_value)
{
    write(2, msg, my_strlen(msg));
    return (return_value);
}
