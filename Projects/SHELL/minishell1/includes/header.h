/*
** EPITECH PROJECT, 2023
** navy_header.h
** File description:
** my_navy header
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
#include <stdlib.h>
#include <sys/wait.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

typedef struct env_s {
    char **env;
    char *oldpwd;
} env_t;

typedef struct exec_s {
    char *name;
    int (*func)(char **arr, env_t *env);
} exec_t;

char **str_to_array(char *av);
char **str_to_array_space(char *av);
char *my_strcat(char *str1, char *str2);
int print_outpout(int ret);
int my_strlen(char *str);
int my_strcmp(char *str1, char *str2);
int my_strccmp(char *str, char *comp, char end);
int nb_elements_array(char **arr);
int my_getnbr(const char *str, int ind);

int error_cases(int ac, char **av);
int minishell(int ac, char **av, env_t *env);
int execute_command(char **com, env_t *env);

int exit_func(char **arr, env_t *env);
int cd_func(char **arr, env_t *env);
int env_func(char **arr, env_t *env);
int unsetenv_func(char **arr, env_t *env);
int setenv_func(char **arr, env_t *env);
