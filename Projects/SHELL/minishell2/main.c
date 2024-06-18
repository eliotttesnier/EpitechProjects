/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "includes/header.h"

int main(int ac, char **av, char **env)
{
    env_t env_struct = {env, NULL};

    if (env[0] == NULL)
        return (my_perror("No environment.\n", 84));
    return (minishell(ac, av, &env_struct));
}
