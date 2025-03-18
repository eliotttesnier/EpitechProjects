/*
** EPITECH PROJECT, 2024
** header
** File description:
** header file
*/

#pragma once

#include <my_lib.h>
#include <macro.h>

typedef enum type_e {
    ROOM = 0,
    START,
    END
} type_t;

int amazed(int ac);

typedef struct path_s {
    char *id;
    int x;
    int y;
    struct path_s *next;
} path_t;

typedef struct map_s {
    int nb_rbt;
    int length;
    path_t *path;
    struct map_s *next;
} map_t;

typedef struct room_s {
    char *id;
    int x;
    int y;
    type_t room_type;
    struct room_s *next;
} rooms_t;

typedef struct tunnel_s {
    char *id_1;
    char *id_2;
    struct tunnel_s *next;
} tunnels_t;

typedef struct mapstat_s {
    int nb_robots;
    rooms_t *rooms;
    tunnels_t *tunnels;
} mapstat_t;

typedef struct parsing_s {
    char *line;
    bool start;
    bool end;
    bool ignore;
    struct parsing_s *next;
} parsing_t;

int amazed(int ac);

// Parsing

void fill_pars(parsing_t **pars);
int words_number(char *line);
void remove_coms(char *line);
void remove_commands(parsing_t **pars);
bool is_end(parsing_t *pars);
bool is_start(parsing_t *pars);
int valid_nb_robots(char *line);
int rooms_error(parsing_t *pars);
int tunnels_error(parsing_t *pars);
parsing_t *get_first_tunnel(parsing_t *pars);

// Format

char **format_arr(char **file);
char **del_in_array(char **arr, int i);
char *remove_spaces(char *line);
void filmap_tstat(parsing_t *pars, mapstat_t *mapstat);

// Error cases on rooms

int already_room(parsing_t *pars, parsing_t *new);
int unknown_tunnel(parsing_t *pars, parsing_t *new);

// Algo

bool is_a_comment(char *line);
bool is_a_command(char *line);
