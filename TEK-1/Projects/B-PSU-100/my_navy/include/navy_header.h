/*
** EPITECH PROJECT, 2023
** navy_header.h
** File description:
** my_navy header
*/

#pragma once
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include "macro_header.h"
#include <time.h>

typedef struct game_stat {
    char **my_map;
    char **opp_map;
    int pid;
    int x;
    int y;
    bool process;
} game_s;

extern game_s *game_stat;

int mini_printf(const char *format, ...);
int my_power(int nb, int p);
int my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
char *my_strcpy(char *src);
int my_strlen(char const *str);
int my_nbrlen(int nbr);
double my_root(double square);
int my_getnbr(char *, int);
int usleep(useconds_t useconds);

int hub_error(int ac, char **av);
int argv_error(int ac, char **av);
int check_file(char *filepath);

void check_impact(int sig, siginfo_t *info, void *context);
int check_input(char *input);

void wait_for_opp_1(void);
void connect_to_opp_2(int pid);
void send_coords(int x, int y);

char **create_opp_map(void);
char **create_map(char *buff);

void disp_maps(bool force);

void right_pos(int sig, siginfo_t *info, void *context);
void wrong_pos(int sig, siginfo_t *info, void *context);
void get_y_co(int sig, siginfo_t *info, void *context);
void get_x_co(int sig, siginfo_t *info, void *context);
void get_turn(int sig, siginfo_t *info, void *context);
void disp_waiting(void);
int check_win(void);
