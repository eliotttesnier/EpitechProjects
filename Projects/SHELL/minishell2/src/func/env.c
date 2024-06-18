/*
** EPITECH PROJECT, 2024
** env
** File description:
** env
*/

#include "../../includes/header.h"

int env_func(char **arr, env_t *env)
{
    if (arr[1] != NULL)
        return (84);
    for (int i = 0; env->env[i] != NULL; i++) {
        write(1, env->env[i], my_strlen(env->env[i]));
        write(1, "\n", 1);
    }
    return (0);
}
