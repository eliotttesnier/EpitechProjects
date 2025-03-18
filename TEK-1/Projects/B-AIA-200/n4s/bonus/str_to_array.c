/*
** EPITECH PROJECT, 2024
** n4s
** File description:
** str_to_array
*/

#include "header.h"

int nb_words(char *line, char *ban)
{
    char *buff = NULL;
    int nb = 0;

    buff = strtok(line, ban);
    while (buff != NULL) {
        nb++;
        buff = strtok(NULL, ban);
    }
    return (nb);
}

char **str_to_array(char *line, char *ban)
{
    char *copy = strdup(line);
    int nb = nb_words(copy, ban);
    int i = 0;
    char **new = malloc(sizeof(char *) * (nb + 1));

    free(copy);
    new[nb] = NULL;
    new[i] = strtok(line, ban);
    while (new[i] != NULL) {
        i++;
        new[i] = strtok(NULL, ban);
    }
    return (new);
}
