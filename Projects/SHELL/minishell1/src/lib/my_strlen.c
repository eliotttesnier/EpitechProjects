/*
** EPITECH PROJECT, 2024
** my_strlen.c
** File description:
** my_stlen.c
*/

#include "../../includes/header.h"

int my_strlen(char *str)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++);
    return (i);
}
