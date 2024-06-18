/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** words_number
*/

#include "header.h"

int words_number(char *line)
{
    char **temp = NULL;
    int nb = 0;

    if (line == NULL)
        return (0);
    temp = str_to_array(line, " -\n");
    nb = my_arrlen(temp);
    free_arr(temp);
    return (nb);
}
