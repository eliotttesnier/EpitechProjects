/*
** EPITECH PROJECT, 2024
** bonus
** File description:
** display_cw_winner
*/

#include "corewar_header.h"

void get_winner(map_t *vm, char **winner, bool area)
{
    char *name;
    int len;

    if (area) {
        for (int i = 0; i < vm->nb_prog; i++) {
            if (vm->programs[i] == NULL)
                continue;
            if (vm->programs[i]->id == occurence_winner(vm)[0][0])
                name = strdup(vm->programs[i]->name);
        }
    } else {
        for (int i = 0; i < vm->nb_prog; i++) {
            if (vm->programs[i] == NULL)
                continue;
            name = strdup(vm->programs[i]->name);
        }
    }
    len = strlen(name) + 4;
    for (int i = 0; i < 5; i++) {
        winner[i] = malloc(sizeof(char) * len + 1);
    }
    for (int i = 0; i < len; i++) {
        winner[0][i] = '=';
        winner[4][i] = '=';
    }
    for (int i = 0; i < len; i++) {
        winner[1][i] = ' ';
        winner[2][i] = ' ';
        winner[3][i] = ' ';
    }
    winner[0][0] = '*';
    winner[0][len - 1] = '*';
    winner[1][0] = '|';
    winner[2][0] = '|';
    winner[3][0] = '|';
    winner[1][len - 1] = '|';
    winner[2][len - 1] = '|';
    winner[3][len - 1] = '|';
    winner[4][0] = '*';
    winner[4][len - 1] = '*';
    for (int i = 0; i < (int)strlen(name); i++) {
        winner[2][i + 2] = name[i];
    }
}

void display_win_screen(char **screen, int x, int size)
{
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(12, COLOR_RED, COLOR_BLACK);
    init_pair(13, COLOR_GREEN, COLOR_BLACK);
    init_pair(14, COLOR_BLUE, COLOR_BLACK);
    init_pair(15, COLOR_CYAN, COLOR_BLACK);
    init_pair(16, COLOR_YELLOW, COLOR_BLACK);
    init_pair(17, COLOR_MAGENTA, COLOR_BLACK);

    for (int i = 0; i < 55; i++) {
        for (int j = 0; j < 238; j++) {
            attron(COLOR_PAIR(1));
            if ((IS_NBR(screen[i][j]) == 1 || IS_UCASE(screen[i][j]) == 1))
                attron(COLOR_PAIR(rand() % 6 + 12));
            if (i == 30 && (j > x && j < x + size))
                attron(COLOR_PAIR(1));
            printw("%c", screen[i][j]);
        }
    }
}

void replace_win_text(char **screen, char **text, char **winner)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 38; j++) {
            screen[18 + i][100 + j] = text[i][j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; winner[i][j] != '\0'; j++) {
            screen[28 + i][(238 - (int)strlen(winner[0])) / 2 + j] = winner[i][j];
        }
    }
}

void display_win(map_t *vm, char **text, bool area)
{
    char **screen = malloc(sizeof(char *) * 55);
    char **winner = malloc(sizeof(char *) * 5);
    char base[33] = "0 1 2 3 4 5 6 7 8 9 A B C D E F ";

    get_winner(vm, winner, area);
    for (int i = 0; i < 55; i++) {
        screen[i] = malloc(sizeof(char) * 238);
        for (int j = 0; j < 238; j++) {
            screen[i][j] = base[rand() % 32];
        }
    }
    for (int i = 0; i < 2000; i++) {
        erase();
        for (int j = 0; j < 15; j++) {
            screen[rand() % 55][rand() % 238] = ' ';
        }
        replace_win_text(screen, text, winner);
        display_win_screen(screen, (238 - (int)strlen(winner[0])) / 2, strlen(winner[0]));
        refresh();
        usleep(2500);
    }
}
