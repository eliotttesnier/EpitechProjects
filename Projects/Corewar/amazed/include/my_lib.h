/*
** EPITECH PROJECT, 2024
** lib
** File description:
** my_lib
*/

#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "macro.h"

void my_putchar(char c);
int my_strlen(char *str);
void my_putstr(char *str);
int my_nbrlen(int nbr);
char *my_int_to_str(int nbr);
void my_putnbr(int nbr);
int my_getnbr(char *buffer, int i);
char *my_strdup(char *str);
int my_strcmp(char *one, char *two);
int my_strncmp(char *one, char *two, int nb);
int mini_printf(char *format, ...);
double my_root(double square);
char *my_strcut(char *str, int start, int end);
char *my_strcat(char *one, char *two);
char **my_arrdup(char **arr);
int my_arrlen(char **arr);
int my_perror(char *msg, int return_value);
char **str_to_array(char *av, char *ban);
void free_arr(char **arr);
char **my_pushback_to_arr(char **arr, char *line);
