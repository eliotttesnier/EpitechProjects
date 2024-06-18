/*
** EPITECH PROJECT, 2024
** format_arr.c
** File description:
** removes the useless spaces
*/

#include "include/robot_header.h"

void transform_tabs(char *line)
{
    bool quote = false;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '"')
            quote = !quote;
        if (line[i] == '\t' && quote == false)
            line[i] = ' ';
    }
}

char *remove_beg_space(char *line)
{
    char *formated = malloc(sizeof(char) * my_strlen(line) + 1);
    int beg = 0;

    if (formated == NULL)
        return (NULL);
    for (beg = 0; line[beg] == ' ' || line[beg] == '\t'; beg++);
    for (int i = 0; line[beg] != '\0'; i++) {
        formated[i] = line[beg];
        formated[i + 1] = '\0';
        beg++;
    }
    free(line);
    return (formated);
}

char *remove_comment(char *line)
{
    char *formated;
    bool quotes = false;
    int i = 0;

    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] == '"')
            quotes = !quotes;
        if (line[i] == '#' && quotes == false)
            break;
    }
    if (line[0] == '#')
        return ("\0");
    if (line[i] == '\0')
        return (line);
    formated = my_strcut(line, 0, i - 1);
    free(line);
    return (formated);
}

void format_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        arr[i] = remove_beg_space(arr[i]);
        transform_tabs(arr[i]);
        arr[i] = remove_comment(arr[i]);
    }
}
