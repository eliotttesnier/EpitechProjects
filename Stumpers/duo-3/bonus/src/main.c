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

int retry(void)
{
    size_t size = 0;
    char *buf = NULL;

    while (1) {
        printf("\x1b[34mPlay again ? ");
        printf("(\x1b[32my\x1b[34m/\x1b[31mn\x1b[34m): \x1b[0m");
        getline(&buf, &size, stdin);
        if (strcmp(buf, "y\n") == 0)
            return (1);
        if (strcmp(buf, "n\n") == 0)
            return (0);
    }
    return (0);
}

int hangman(char *path, int nb_tries)
{
    char *pathsave = strdup(path);
    char *word = get_word(path);
    int ret = 0;

    word = sup_spaces(word);
    ret = find_word(word, nb_tries);
    if (retry() == 1)
        return (hangman(pathsave, nb_tries));
    free(word);
    free(pathsave);
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
