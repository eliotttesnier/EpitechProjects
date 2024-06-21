/*
** EPITECH PROJECT, 2024
** duo-3
** File description:
** main
*/

#include "stumper.h"

char *sup_spaces(char *str)
{
    char *temp = strdup(str);
    char *word = strtok(temp, " \t\n");
    char *ret = strdup(word);

    free(temp);
    return (ret);
}

int hangman(char *path, int nb_tries)
{
    char *word = get_word(path);
    int ret = 0;

    word = sup_spaces(word);
    ret = find_word(word, nb_tries);
    free(word);
    return (ret);
}

int main(int ac, char **av)
{
    if (error_cases(ac, av) == -1)
        return (84);
    if (ac == 2)
        return (hangman(av[1], 10));
    return (hangman(av[1], atoi(av[2])));
}
