/*
** EPITECH PROJECT, 2024
** too_many_words
** File description:
** too_any_words
*/

#include "stumper.h"

int nb_words(char *line)
{
    int nb = 0;

    for (int i = 1; line[i - 1] != '\0'; i++) {
        if (line[i] == ' ' && line[i - 1] != ' ' && line[i - 1] != '\t')
            nb++;
        if (line[i] == '\t' && line[i - 1] != '\t' && line[i - 1] != ' ')
            nb++;
        if (line[i] == '\0' && line[i - 1] != '\t' && line[i - 1] != ' ')
            nb++;
    }
    return (nb);
}

int too_many_words(char *buff)
{
    char *temp = strdup(buff);
    char *line = NULL;

    line = strtok(temp, "\n");
    while (line != NULL) {
        if (nb_words(line) != 1)
            return (-1);
        line = strtok(NULL, "\n");
    }
    return (0);
}
