/*
** EPITECH PROJECT, 2024
** valid_redir
** File description:
** valid_redir
*/

#include "../includes/header.h"

int check_left_redir(char **arr, int ind)
{
    if (arr[ind] == NULL)
        return (my_perror("Missing name for redirect.\n", -1));
    if (arr[ind][0] == '|' || arr[ind][0] == '>' || arr[ind][0] == '<')
        return (my_perror("Missing name for redirect.\n", -1));
    for (int i = 0; arr[ind][i] != '\0'; i++) {
        if (arr[ind][i] == '<' || arr[ind][i] == '>' || arr[ind][i] == '|')
            return (my_perror("Ambiguous input redirect.\n", -1));
    }
    for (int i = ind; i >= 0; i--) {
        if (my_strcmp(arr[i], "|") == 0)
            return (my_perror("Ambiguous input redirect.\n", -1));
    }
    return (0);
}

int check_right_redir(char **arr, int ind)
{
    if (arr[ind] == NULL)
        return (my_perror("Missing name for redirect.\n", -1));
    if (arr[ind][0] == '|' || arr[ind][0] == '>' || arr[ind][0] == '<')
        return (my_perror("Missing name for redirect.\n", -1));
    for (int i = 0; arr[ind][i] != '\0'; i++) {
        if (arr[ind][i] == '<' || arr[ind][i] == '>' || arr[ind][i] == '|')
            return (my_perror("Ambiguous output redirect.\n", -1));
    }
    for (int i = ind; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], "|") == 0)
            return (my_perror("Ambiguous output redirect.\n", -1));
    }
    return (0);
}

int valid_redir(char **arr)
{
    int valid = 0;

    for (int i = 0; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], ">") == 0)
            valid += check_right_redir(arr, i + 1);
        if (my_strcmp(arr[i], ">>") == 0)
            valid += check_right_redir(arr, i + 1);
        if (my_strcmp(arr[i], "<") == 0)
            valid += check_left_redir(arr, i + 1);
        if (my_strcmp(arr[i], "<<") == 0)
            valid += check_left_redir(arr, i + 1);
    }
    return ((valid != 0 ? -1 : 0));
}
