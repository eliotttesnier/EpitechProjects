/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** format_arr
*/

#include "header.h"

char *remove_spaces(char *line)
{
    char *temp = NULL;
    char *temp2 = NULL;
    char *ret = NULL;
    char **arr = str_to_array(line, " -\n");

    ret = my_strdup(arr[0]);
    for (int i = 1; arr[i] != NULL; i++) {
        temp = my_strcat(" ", arr[i]);
        temp2 = my_strcat(ret, temp);
        free(ret);
        ret = my_strdup(temp2);
        free(temp);
        free(temp2);
    }
    free(arr);
    return (ret);
}

void format_spaces(char **file)
{
    for (int i = 0; file[i] != NULL; i++) {
        file[i] = remove_spaces(file[i]);
    }
}

char **format_arr(char **file)
{
    format_spaces(file);
    for (int i = 0; file[i] != NULL; i++) {
        if (file[i][0] == '#' && my_strcmp(file[i], "##start") != 1
            && my_strcmp(file[i], "##end") != 1) {
            file = del_in_array(file, i);
            i--;
        }
    }
    return (file);
}
