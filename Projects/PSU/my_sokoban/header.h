/*
** EPITECH PROJECT, 2023
** header.h
** File description:
** header of sokoban
*/

#ifndef SOKOBAN_PROJECT
    #define SOKOBAN_PROJECT

struct o_case {
    int x;
    int y;
    int status;
};

struct player {
    int x;
    int y;
};

typedef struct o_case s_ocase;
typedef struct player s_player;
void right(char **map, s_player *p);
void left(char **map, s_player *p);
void up_input(char **map, s_player *p);
void down(char **map, s_player *p);
int check_stuck(char **map, int nb_lines);
int actualise_o(char **map, int nb_lines, s_ocase **ocases);
s_ocase **get_ocases(char **map, s_ocase **ocases, int nb_lines);
void find_player(char **map, s_player *p, int nb_lines);
char **get_map(char **map, char *file, int *nb_lines, int *maxlen);
int readme(void);
int error_cases(char *file);
void check_term_size(char **map, int nb_lines, int maxlen);
void display_map(char **map, int nb_lines);

#endif /* !SOKOBAN_PROJECT */
