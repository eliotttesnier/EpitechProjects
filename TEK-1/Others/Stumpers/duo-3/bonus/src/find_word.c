/*
** EPITECH PROJECT, 2024
** hangman
** File description:
** find word
*/
#include "stumper.h"

void replace_hide(char *hide, char *word)
{
    for (int i = 0; word[i] != '\0'; i++) {
        hide[i] = word[i];
        hide[i + 1] = '\0';
    }
}

static char get_the_letter(char *line, char *word, char *hide, int *pts)
{
    size_t len = 0;

    if (getline(&line, &len, stdin) < 0)
        return 84;
    printf("\x1b[0m");
    if (strncmp(line, word, strlen(word) - 1) == 0) {
        *pts = *pts + 10;
        replace_hide(hide, word);
        printf("\x1b[31mG\x1b[32mG \x1b[33mF\x1b[34mi\x1b[35mr\x1b[36ms");
        printf("\x1b[31mt \x1b[32mt\x1b[33mr\x1b[34my \x1b[35m-\x1b[36m>");
        printf(" \x1b[31m+\x1b[32m1\x1b[33m0 \x1b[34mp\x1b[35mt\x1b[36ms");
        printf(" \x1b[31m!\x1b[32m!\n\x1b[0m");
        return (0);
    }
    if (strlen(line) > 2) {
        printf("Your letter: \x1b[33m");
        return (get_the_letter(line, word, hide, pts));
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
        printf("\x1b[32m\nCongratulations!\n\x1b[0m");
        return 0;
    }
    return 1;
}

static int loose_condition(char *hide, int tries)
{
    if (tries == 0) {
        printf("%s\nTries: %i\n\n", hide, tries);
        printf("\x1b[31mYou lost!\n\x1b[0m");
        return 1;
    }
    return 0;
}

void win_pts(int *pts, int *tries)
{
    size_t size = 0;
    char *buf = NULL;

    while (1) {
        printf("\x1b[34mBuy 1 try for 5 points ? ");
        printf("(\x1b[32my\x1b[34m/\x1b[31mn\x1b[34m): \x1b[0m");
        getline(&buf, &size, stdin);
        if (strcmp(buf, "y\n") == 0) {
            *pts = *pts - 5;
            *tries = *tries + 1;
            return;
        }
        if (strcmp(buf, "n\n") == 0)
            return;
    }
}

static int game_loop(char *word, char *hide, int *tries, char letter)
{
    char *line = NULL;
    static int pts = 0;

    printf("%s\n", hide);
    printf("Tries: %i\n\n", *tries);
    printf("Your letter: \x1b[33m");
    letter = get_the_letter(line, word, hide, &pts);
    if (replace_stars(word, hide, letter) == 0 && letter != 0) {
        printf("\x1b[31m%c: is not in this word\n\x1b[0m", letter);
        *tries = *tries - 1;
        pts = 0;
    }
    printf("Number of points: %i\n", pts);
    if (pts >= 5)
        win_pts(&pts, tries);
    pts ++;
    return 0;
}

int find_word(char *word, int tries)
{
    char *hide = malloc(sizeof(char) * strlen(word));
    char letter = '\0';

    for (int i = 0; i != (int)strlen(word); i ++) {
        hide[i] = '*';
    }
    hide[strlen(word)] = '\0';
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
