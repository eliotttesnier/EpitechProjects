/*
** EPITECH PROJECT, 2024
** arg_to_array
** File description:
** arg_to_array
*/

#include "../include/my_lib.h"

int is_ban(char letter, char *ban)
{
    for (int i = 0; ban[i] != '\0'; i++) {
        if (letter == ban[i])
            return (1);
    }
    return (0);
}

int first_char(char *av, char *ban)
{
    int i = 0;

    for (i = 0; av[i] != '\0'; i++) {
        if (is_ban(av[i], ban) == 0)
            return i;
    }
    return (i);
}

int nb_letters(char *str, int ind, char *ban)
{
    int nb = 0;

    for (int i = ind; is_ban(str[i], ban) != 1 && str[i] != '\0'; i++) {
        nb += 1;
    }
    return (nb);
}

int nb_words(char *arg, char *ban)
{
    int nb = 1;

    if (is_ban(arg[0], ban) == 1)
        nb = 0;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (i == 0)
            nb = nb;
        if (is_ban(arg[i], ban) == 0 && is_ban(arg[i - 1], ban) == 1)
            nb += 1;
    }
    return (nb);
}

char **str_to_array(char *av, char *ban)
{
    int words = nb_words(av, ban);
    char **arr = malloc(sizeof(char *) * (words + 1));
    int letters = 0;
    int ind = first_char(av, ban);

    arr[words] = NULL;
    for (int i = 0; i < words; i++) {
        letters = nb_letters(av, ind, ban);
        arr[i] = malloc(sizeof(char) * (letters + 1));
        for (int j = 0; j < letters && av[ind] != '\0'; j++) {
            arr[i][j] = av[ind];
            ind += 1;
        }
        arr[i][letters] = '\0';
        for (ind = ind; is_ban(av[ind], ban) == 1 && av[ind] != '\0'; ind++);
    }
    return (arr);
}
