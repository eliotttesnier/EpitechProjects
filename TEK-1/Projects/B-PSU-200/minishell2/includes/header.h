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
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

typedef struct env_s {
    char **env;
    char *oldpwd;
} env_t;

typedef struct exec_s {
    char *name;
    int (*func)(char **arr, env_t *env);
} exec_t;

typedef struct command_s {
    char *bin;
    char **args;
    int fd;
    int in;
    struct command_s *redi;
    struct command_s *next;
    int (*func)(char **arr, env_t *env);
} command_t;

char **str_to_array(char *av, char *ban);
char *my_strcat(char *str1, char *str2);
char *my_strdup(char *str);
int print_outpout(int ret);
int my_perror(char *msg, int ret);
void free_arr(char **arr);
int my_strlen(char *str);
int my_strcmp(char *str1, char *str2);
int my_strccmp(char *str, char *comp, char end);
int nb_elements_array(char **arr);
int my_getnbr(const char *str, int ind);

int error_cases(int ac, char **av);
int minishell(int ac, char **av, env_t *env);
int check_path(command_t *com, env_t *env);
int find_func(command_t *com, env_t *env);
int before_exec(command_t *com, env_t *env);
int exec_pipe(command_t *com, env_t *env, int in_fd);
int exec_com(command_t *com, env_t *env);
int process_command(char *com, env_t *env, int sdin, int sdout);

int exit_func(char **arr, env_t *env);
int cd_func(char **arr, env_t *env);
int env_func(char **arr, env_t *env);
int unsetenv_func(char **arr, env_t *env);
int setenv_func(char **arr, env_t *env);

void check_redirections(command_t *com, char *line);
void remove_redirect(command_t *new);
command_t *free_lcom(command_t *lcom, int sdin, int sdout);
int valid_redir(char **arr);
int open_simple_right(char *path);
int open_double_right(char *path);
int open_simple_left(char *path);
int open_double_left(char *word);

int perm_denied(char *binary);
int have_perm(char *path);
int is_dir(char *path);
int command_not_found(char *binary);
int failed_exec(char *binary, int err);
int crash(int wstatus);
