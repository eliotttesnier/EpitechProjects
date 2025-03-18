/*
** EPITECH PROJECT, 2024
** arg_to_array
** File description:
** arg_to_array
*/

#include "../../includes/header.h"

int is_banable(char letter)
{
    if (letter == ' ' || letter == ':' || letter == '=' || letter == '\t')
        return (1);
    return (0);
}

int first_char(char *av)
{
    int i = 0;

    for (i = 0; av[i] != '\0'; i++) {
        if (is_banable(av[i]) == 0)
            return i;
    }
    return (i);
}

int nb_letters(char *str, int ind)
{
    int nb = 0;

    for (int i = ind; is_banable(str[i]) != 1 && str[i] != '\0'; i++) {
        nb += 1;
    }
    return (nb);
}

int nb_words(char *arg)
{
    int nb = 1;

    if (is_banable(arg[0]) == 1)
        nb = 0;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (i == 0)
            nb = nb;
        if (is_banable(arg[i]) == 0 && is_banable(arg[i - 1]) == 1)
            nb += 1;
    }
    return (nb);
}

char **str_to_array(char *av)
{
    int words = nb_words(av);
    char **arr = malloc(sizeof(char *) * words + 1);
    int letters = 0;
    int ind = first_char(av);

    arr[words] = NULL;
    for (int i = 0; i < words; i++) {
        letters = nb_letters(av, ind);
        arr[i] = malloc(sizeof(char) * letters);
        for (int j = 0; j < letters; j++) {
            arr[i][j] = av[ind];
            ind += 1;
        }
        for (ind = ind; is_banable(av[ind]) == 1 && av[ind] != '\0'; ind++);
    }
    return (arr);
}
