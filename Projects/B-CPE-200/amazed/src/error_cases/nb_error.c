/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** number_pars
*/

#include "header.h"

int valid_nb_robots(char *line)
{
    char **arr = str_to_array(line, " \t\n");

    if (arr == NULL)
        return (my_perror("Invalid script : empty line.\n", -1));
    if (my_arrlen(arr) != 1) {
        free_arr(arr);
        return (my_perror("Invalid script : number of robots.\n", -1));
    }
    for (int i = 0; arr[0][i] != '\0'; i++) {
        if (IS_NBR(arr[0][i]) == 0) {
            free_arr(arr);
            return (my_perror("Invalid script : number of robots.\n", -1));
        }
    }
    if (my_getnbr(arr[0], 0) == 0)
        return (my_perror("Invalid script : number of robots.\n", -1));
    mini_printf("#number_of_robots\n%d\n", my_getnbr(arr[0], 0));
    free_arr(arr);
    return (0);
}
