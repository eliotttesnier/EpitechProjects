/*
** EPITECH PROJECT, 2024
** setenv
** File description:
** setenv
*/

#include "../../includes/header.h"

static int alpha_char(void)
{
    write(2, "setenv: Variable name must", 26);
    write(2, " contain alphanumeric characters.\n", 34);
    return (1);
}

int add_element(char **arr, env_t *env)
{
    char **copy = malloc(sizeof(char *) * (nb_elements_array(env->env) + 1));
    int i = 0;

    for (i = 0; env->env[i] != NULL; i++) {
        copy[i] = malloc(sizeof(char) * my_strlen(env->env[i]));
    }
    if (nb_elements_array(arr) == 3)
        copy[i] = malloc((my_strlen(arr[1]) + my_strlen(arr[2]) + 1));
    else
        copy[i] = malloc((my_strlen(arr[1] + 1)));
    for (i = 0; env->env[i] != NULL; i++) {
        copy[i] = env->env[i];
    }
    if (nb_elements_array(arr) == 3)
        copy[i] = my_strcat(my_strcat(arr[1], "="), arr[2]);
    else
        copy[i] = my_strcat(arr[1], "=");
    copy[i + 1] = NULL;
    env->env = copy;
    return (0);
}

int existing(char **arr, env_t *env, int i)
{
    char *new;

    if (nb_elements_array(arr) == 2)
        new = my_strcat(arr[1], "=");
    else
        new = my_strcat(my_strcat(arr[1], "="), arr[2]);
    env->env[i] = new;
    return (0);
}

int check_existing(char **arr, env_t *env)
{
    for (int i = 0; env->env[i] != NULL; i++) {
        if (my_strccmp(arr[1], env->env[i], '=') == 0)
            return (existing(arr, env, i));
    }
    return (add_element(arr, env));
}

int setenv_func(char **arr, env_t *env)
{
    if (arr[1] == NULL)
        return (env_func(arr, env));
    if (nb_elements_array(arr) > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        return (1);
    }
    for (int i = 0; arr[1][i] != '\0'; i++) {
        if (IS_LETTER(arr[1][i]) == 0 && IS_NUMBER(arr[1][i]) == 0)
            return (alpha_char());
    }
    return (check_existing(arr, env));
}
