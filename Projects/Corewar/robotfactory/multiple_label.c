/*
** EPITECH PROJECT, 2024
** multiple label
** File description:
** multiple label
*/

#include "include/robot_header.h"

int fill_labels(char *line, char **labels, int ind)
{
    int j = 0;

    for (j = 0; line[j] != '\0'; j++) {
        if (line[j] == ':' && line[j + 1] == ' ')
            break;
    }
    if (line[j] == '\0')
        return (0);
    labels[ind] = my_strcut(line, 0, j);
    return (1);
}

int get_nb_labels(char **body)
{
    int nb = 0;

    for (int i = 0; body[i] != NULL; i++) {
        for (int j = 0; body[i][j] != '\0'; j++) {
            nb += (body[i][j] == ':' && body[i][j + 1] == ' ' ? 1 : 0);
        }
    }
    return (nb);
}

int same_name(char **labels, int i)
{
    for (int j = i + 1; labels[j] != NULL; j++) {
        if (my_strcmp(labels[i], labels[j]) == 1)
            return (1);
    }
    return (0);
}

int multiple_label(char **body)
{
    int ind = 0;
    char **labels = malloc(sizeof(char *) * (get_nb_labels(body) + 1));

    for (int i = 0; body[i] != NULL; i++) {
        ind += fill_labels(body[i], labels, ind);
    }
    for (int i = 0; labels[i] != NULL; i++) {
        if (same_name(labels, i) == 1)
            return (my_perror("Multiple def same label.\n", -1));
    }
    return (0);
}
