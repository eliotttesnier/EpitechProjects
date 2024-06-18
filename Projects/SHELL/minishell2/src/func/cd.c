/*
** EPITECH PROJECT, 2024
** cd
** File description:
** cd
*/

#include "../../includes/header.h"

static int too_many(void)
{
    write(2, "cd : too many arguments\n", 24);
    return (1);
}

static int not_found(char *fi, int ret)
{
    char *str = my_strcat(": ", my_strcat(strerror(errno), ".\n"));

    if (fi[my_strlen(fi) - 1] == '!')
        fi[my_strlen(fi) - 1] = '\0';
    write(2, my_strcat(fi, str), my_strlen(str) + my_strlen(fi));
    return (1);
}

void change_pwd(env_t *env, char *pwd)
{
    for (int i = 0; env->env[i] != NULL; i++) {
        if (my_strccmp("PWD", env->env[i], '=') == 0) {
            env->env[i] = pwd;
            return;
        }
    }
}

char *get_pwd(env_t *env)
{
    size_t size = 1;
    char *cwd = malloc(sizeof(char) * size);

    while (getcwd(cwd, size) == NULL) {
        free(cwd);
        size += 1;
        cwd = malloc(sizeof(char) * size);
    }
    return (cwd);
}

char *get_home(env_t *env)
{
    int i = 0;
    int j = 0;
    char *home = NULL;

    for (i = 0; env->env[i] != NULL; i++) {
        if (my_strccmp("HOME", env->env[i], '=') == 0) {
                break;
            }
    }
    for (j = 5; env->env[i][j] != '\0'; j++);
    home = malloc(sizeof(char) * j - 4);
    for (j = 5; env->env[i][j] != '\0'; j++) {
        home[j - 5] = env->env[i][j];
        home[j - 4] = '\0';
    }
    return (home);
}

static int go_to_prev(env_t *env)
{
    int ret = 0;
    char *old = get_pwd(env);

    if (env->oldpwd == NULL) {
        write(2, ": No such file or directory.\n", 30);
        return (1);
    }
    ret = chdir(env->oldpwd);
    if (ret != 0)
        return (not_found(env->oldpwd, ret));
    env->oldpwd = old;
    change_pwd(env, my_strcat("PWD=", get_pwd(env)));
    return (ret);
}

static int go_to_path(env_t *env, char *path, char *arg)
{
    int ret = 0;
    char *old = get_pwd(env);

    ret = chdir(path);
    if (ret != 0)
        return (not_found(arg, ret));
    env->oldpwd = old;
    change_pwd(env, my_strcat("PWD=", get_pwd(env)));
    return (ret);
}

static int go_to_home(env_t *env)
{
    int ret = 0;
    char *old = get_pwd(env);

    ret = chdir(get_home(env));
    if (ret != 0)
        return (84);
    env->oldpwd = old;
    change_pwd(env, my_strcat("PWD=", get_pwd(env)));
    return (ret);
}

int cd_func(char **arr, env_t *env)
{
    char *str;
    int ret = 0;

    if (arr[1] == NULL)
        return (go_to_home(env));
    if (my_strcmp(arr[1], "~") == 0 || my_strcmp(arr[1], "home") == 0)
        return (go_to_home(env));
    if (arr[2] != NULL)
        return (too_many());
    if (arr[1][0] == '/')
        return (go_to_path(env, arr[1], arr[1]));
    if (my_strcmp(arr[1], "-") == 0)
        return (go_to_prev(env));
    str = my_strcat(my_strcat(get_pwd(env), "/"), arr[1]);
    return (go_to_path(env, str, arr[1]));
}
