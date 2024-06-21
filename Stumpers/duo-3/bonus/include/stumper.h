/*
** EPITECH PROJECT, 2024
** stumper
** File description:
** stumper
*/

#pragma once

#define _XOPEN_SOURCE 700
#define IS_LETTER(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? 1 : 0)
#define IS_UPC(c) (c >= 'A' && c <= 'Z' ? 1 : 0)
#define IS_LOWC(c) (c >= 'a' && c <= 'z' ? 1 : 0)
#define IS_NUMBER(c) (c >= '0' && c <= '9' ? 1 : 0)
#define ABS(nb) (nb < 0 ? nb * -1 : nb)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>

typedef struct dict {
    char *word;
    struct dict *next;
} dict_t;

int error_cases(int ac, char **av);
int get_size(char *path);
char *get_word(char *path);
int find_word(char *word, int tries);
int too_many_words(char *buff);
