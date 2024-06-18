/*
** EPITECH PROJECT, 2024
** header
** File description:
** header file
*/

#pragma once

#include <macro.h>
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
#include <SFML/Audio.h>

typedef struct direction_s {
    float front;
    float rf;
    float right;
    float lf;
    float left;
} direction_t;

char **str_to_array(char *line, char *ban);

void direction(float dir, bool *end);
void forward(float nb, bool *end);
void stop(void);
void start(void);
char *get_output(void);
bool reached_end(char *line);
