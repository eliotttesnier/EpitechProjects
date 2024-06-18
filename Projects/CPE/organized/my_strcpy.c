/*
** EPITECH PROJECT, 2023
** my_strcpy
** File description:
** strcpy
*/

#include "libshell/shell.h"

void my_strcpy(char *str, char *tocopy)
{
    int len = pfmy_strlen(tocopy);

    for (int i = 0; tocopy[i] != '\0'; i++) {
        str[i] = tocopy[i];
    }
    str[len] = '\0';
}
