/*
** EPITECH PROJECT, 2024
** bonus
** File description:
** display_cw_final
*/

#include "corewar_header.h"

void replace_draw_text(char **screen, char **text)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 30; j++) {
            screen[25 + i][104 + j] = text[i][j];
        }
    }
}

void display_draw_screen(char **screen)
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

static void display_draw(char **text)
{
    char **screen = malloc(sizeof(char *) * 55);
    char base[33] = "0 1 2 3 4 5 6 7 8 9 A B C D E F ";

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
        replace_draw_text(screen, text);
        display_draw_screen(screen);
        refresh();
        usleep(2500);
    }
}

static int get_nb_alive(map_t *vm)
{
    int nb_alive = 0;

    for (int i = 0; i < vm->nb_prog; i++) {
        if (vm->programs[i] == NULL)
            continue;
        nb_alive++;
    }
    return (nb_alive);
}

void display_cw_winner(map_t *vm, bool area, bool draw_state)
{
    char **win = malloc(sizeof(char *) * 5);
    char **draw = malloc(sizeof(char *) * 5);
    char win_model[5][39] = {
        " _       _______   ___   ____________ ",
        "| |     / /  _/ | / / | / / ____/ __ \\",
        "| | /| / // //  |/ /  |/ / __/ / /_/ /",
        "| |/ |/ // // /|  / /|  / /___/ _, _/ ",
        "|__/|__/___/_/ |_/_/ |_/_____/_/ |_|  "
    };
    char draw_model[5][31] = {
        "    ____  ____  ___ _       __",
        "   / __ \\/ __ \\/   | |     / /",
        "  / / / / /_/ / /| | | /| / / ",
        " / /_/ / _, _/ ___ | |/ |/ /  ",
        "/_____/_/ |_/_/  |_|__/|__/   "
    };

    for (int i = 0; i < 5; i++) {
        win[i] = strdup(win_model[i]);
        draw[i] = strdup(draw_model[i]);
    }
    if (area == true && draw_state == true) {
        display_draw(draw);
    } else if (area == true && draw_state == false) {
        display_win(vm, win, area);
    }
    if (get_nb_alive(vm) == 0) {
        display_draw(draw);
    } else {
        display_win(vm, win, area);
    }
}
