/*
** EPITECH PROJECT, 2024
** exit
** File description:
** exit
*/

#include "../../includes/header.h"

int syntax_error(char **arr)
{
    if (arr[2] != NULL) {
        write(2, "exit: Expression Syntax.\n", 25);
        return (1);
    }
    for (int i = 0; arr[1][i] != '\0'; i++) {
        if (i == 0 && arr[1][1] != '-' && IS_NUMBER(arr[1][i] == 0)) {
            write(2, "exit: Expression Syntax.\n", 25);
            return (1);
        }
        if (IS_NUMBER(arr[1][i]) == 0) {
            write(2, "exit: Expression Syntax.\n", 25);
            return (1);
        }
    }
    return (0);
}

int exit_func(char **arr, env_t *env)
{
    int nb = 0;

    if (arr[1] == NULL) {
        write(1, "exit\n", 5);
        exit(0);
    }
    if (syntax_error(arr) == 1)
        return (1);
    write(1, "exit\n", 5);
    nb = my_getnbr(arr[1], 0);
    if (nb >= 0)
        exit(nb % 256);
    else {
        while (nb < 0) {
            nb = 256 + nb;
        }
        exit(nb);
    }
    return (0);
}
