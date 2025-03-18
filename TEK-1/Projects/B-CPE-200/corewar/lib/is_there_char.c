/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** is_there_char
*/

#include "my_lib.h"

bool is_there_char(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return (true);
    }
    return (false);
}
