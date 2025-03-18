/*
** EPITECH PROJECT, 2024
** my_perror
** File description:
** my_perror
*/

#include "../../includes/header.h"

int my_perror(char *msg, int ret)
{
    write(2, msg, my_strlen(msg));
    return (ret);
}
