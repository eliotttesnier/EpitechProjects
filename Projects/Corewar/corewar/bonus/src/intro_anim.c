/*
** EPITECH PROJECT, 2024
** bonus
** File description:
** intro_anim
*/

#include "corewar_header.h"

void display_intro_screen(char **screen)
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
            if (IS_NBR(screen[i][j]) == 1 || IS_UCASE(screen[i][j]) == 1)
                attron(COLOR_PAIR(rand() % 6 + 12));
            printw("%c", screen[i][j]);
        }
    }
}

void replace_text(char **screen, char **text)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 49; j++) {
            screen[25 + i][94 + j] = text[i][j];
        }
    }
}

void display_intro(void)
{
    char base[17] = "0123456789ABCDEF";
    char **screen = malloc(sizeof(char *) * 55);
    char **text = malloc(sizeof(char *) * 5);
    char model[5][50] = {
        "   __________  ____  _______       _____    ____ ",
        "  / ____/ __ \\/ __ \\/ ____/ |     / /   |  / __ \\",
        " / /   / / / / /_/ / __/  | | /| / / /| | / /_/ /",
        "/ /___/ /_/ / _, _/ /___  | |/ |/ / ___ |/ _, _/ ",
        "\\____/\\____/_/ |_/_____/  |__/|__/_/  |_/_/ |_|  "
    };
    for (int i = 0; i < 5; i++) {
        text[i] = strdup(model[i]);
    }
    for (int i = 0; i < 55; i++) {
        screen[i] = malloc(sizeof(char) * 238);
        for (int j = 0; j < 238; j++) {
            screen[i][j] = ' ';
        }
    }
    for (int i = 0; i < 2000; i++) {
        erase();
        screen[rand() % 55][rand() % 238] = base[rand() % 16];
        replace_text(screen, text);
        display_intro_screen(screen);
        refresh();
        usleep(2500);
    }
}
