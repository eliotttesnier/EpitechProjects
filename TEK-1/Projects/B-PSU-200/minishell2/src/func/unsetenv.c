/*
** EPITECH PROJECT, 2024
** unsetenv
** File description:
** unsetenv
*/

#include "../../includes/header.h"

int check_arg(char **av, env_t *env, int i)
{
    for (int j = 1; av[j] != NULL; j++) {
        if (my_strccmp(av[j], env->env[i], '=') == 0)
            return (-1);
    }
    return (0);
}

int suppression(char **av, env_t *env)
{
    char **copy = malloc(sizeof(char *) * nb_elements_array(env->env));
    int i_copy = 0;

    for (int i = 0; env->env[i] != NULL; i++) {
        copy[i] = malloc(sizeof(char) * my_strlen(env->env[i]));
    }
    for (int i = 0; env->env[i] != NULL; i++) {
        if (check_arg(av, env, i) == 0) {
            copy[i_copy] = env->env[i];
            i_copy += 1;
        }
    }
    copy[i_copy] = NULL;
    for (int i = 0; copy[i] != NULL; i++) {
        env->env[i] = copy[i];
    }
    env->env[i_copy] = NULL;
    free(copy);
    return (0);
}

int unsetenv_func(char **arr, env_t *env)
{
    if (arr[1] == NULL) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return (1);
    }
    for (int i = 1; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], "*") == 0)
            return (1);
    }
    return (suppression(arr, env));
}
