/*
** EPITECH PROJECT, 2024
** hangman
** File description:
** find word
*/
#include "stumper.h"

static char get_the_letter(char *line)
{
    size_t len = 0;

    if (getline(&line, &len, stdin) < 0) {
        return 84;
    }
    if (strlen(line) > 2) {
        printf("Your letter: ");
        return (get_the_letter(line));
    }
    return line[0];
}

static int replace_stars(char *word, char *hide, char letter)
{
    int len_word = strlen(word);
    int good_letter = 0;

    for (int i = 0; i != len_word; i ++) {
        if (word[i] == letter) {
            hide[i] = word[i];
            good_letter = 1;
        }
    }
    return good_letter;
}

static int win_condition(char *word, char *hide, int tries)
{
    if (strcmp(word, hide) == 0) {
        printf("%s\nTries: %i\n", hide, tries);
        printf("\nCongratulations!\n");
        return 0;
    }
    return 1;
}

static int loose_condition(char *hide, int tries)
{
    if (tries == 0) {
        printf("%s\nTries: %i\n\n", hide, tries);
        printf("You lost!\n");
        return 1;
    }
    return 0;
}

static int game_loop(char *word, char *hide, int *tries, char letter)
{
    char *line = NULL;

    printf("%s\n", hide);
    printf("Tries: %i\n\n", *tries);
    printf("Your letter: ");
    letter = get_the_letter(line);
    if (replace_stars(word, hide, letter) == 0) {
        printf("%c: is not in this word\n", letter);
        *tries = *tries - 1;
    }
    return 0;
}

int find_word(char *word, int tries)
{
    char *hide = malloc(sizeof(char) * strlen(word));
    int len_word = strlen(word);
    char letter = '\0';

    for (int i = 0; i != len_word; i ++) {
        hide[i] = '*';
    }
    while (1) {
        game_loop(word, hide, &tries, letter);
        if (loose_condition(hide, tries) == 1) {
            free(hide);
            return (1);
        }
        if (win_condition(word, hide, tries) == 0) {
            free(hide);
            return (0);
        }
    }
    free(hide);
    return 0;
}
