/*
** EPITECH PROJECT, 2024
** check_labels
** File description:
** check for labels
*/

#include "include/op.h"
#include "include/robot_header.h"

int label_exist(char **body, char *label_name)
{
    int end = 0;
    char *temp;

    if (label_name == NULL)
        return (-1);
    for (int i = 0; body[i] != NULL; i++) {
        for (end = 0; body[i][end] != ' ' && body[i][end] != '\0'; end++);
        temp = my_strcut(body[i], 0, end - 1);
        if (my_strcmp(temp, my_strcat(label_name, ":")) == 1)
            return (1);
    }
    return (my_perror("Label doesn't exist.\n", -1));
}

static int is_char_valid(char charac)
{
    for (int i = 0; LABEL_CHARS[i] != '\0'; i++) {
        if (charac == LABEL_CHARS[i])
            return (1);
    }
    return (0);
}

char *get_label_name(char **body, int i, int j)
{
    int beg = j;
    int end = j;

    for (j = j; body[i][j] != '\0'; j++) {
        if (body[i][j] == ',' || body[i][j] == ' ')
            break;
        if (is_char_valid(body[i][j]) == 0)
            return (NULL);
        end = j;
    }
    if (beg == end)
        return (NULL);
    return my_strcut(body[i], beg, end);
}

int find_label(char **body, int ind)
{
    int existing = 0;

    for (int j = 0; body[ind][j] != '\0'; j++) {
        if (body[ind][j] == ':' && body[ind][j + 1] != ' '
            && body[ind][j + 1] != '\0')
            existing = label_exist(body, get_label_name(body, ind, j + 1));
        if (existing == -1)
            return (-1);
    }
    return (existing);
}
