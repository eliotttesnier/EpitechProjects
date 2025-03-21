/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** write_prompt
*/

#include "mysh.h"

void write_prompt(env_t *env)
{
    char *hostname = get_env_var("HOSTNAME", env->env_cpy);
    char *user = get_env_var("USER", env->env_cpy);
    char *pwd = getcwd(NULL, 0);
    char *dir = pwd;

    while (dir && my_strstr(dir, "/")) {
        dir = my_strstr(dir, "/") + 1;
    }
    printf("\033[31m");
    printf("[%s", (user == NULL ? "user" : user));
    printf("@%s", (hostname == NULL ? "hostname" : hostname));
    printf(" %s]$ ", (dir == NULL ? "pwd" : dir));
    printf("\033[0m");
    if (pwd != NULL)
        free(pwd);
}

void write_prompt_without_env(void)
{
    char *hostname = getenv("HOSTNAME");
    char *user = getenv("USER");
    char *pwd = getcwd(NULL, 0);
    char *dir = pwd;

    while (dir && my_strstr(dir, "/")) {
        dir = my_strstr(dir, "/") + 1;
    }
    printf("\033[31m");
    printf("[%s", (user == NULL ? "user" : user));
    printf("@%s", (hostname == NULL ? "hostname" : hostname));
    printf(" %s]$ ", (dir == NULL ? "pwd" : dir));
    printf("\033[0m");
    fflush(stdout);
}

int get_nbr_line_new_prompt(void)
{
    char *hostname = getenv("HOSTNAME");
    char *user = getenv("USER");
    char *pwd = getcwd(NULL, 0);
    char *dir = pwd;

    while (dir && my_strstr(dir, "/")) {
        dir = my_strstr(dir, "/") + 1;
    }
    return (my_strlen(user) + my_strlen(hostname) + my_strlen(dir) + 4);
}
