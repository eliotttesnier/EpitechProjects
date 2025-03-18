/*
** EPITECH PROJECT, 2024
** failed_exec
** File description:
** failed_exec
*/

#include "../includes/header.h"

int crash(int wstatus)
{
    if (wstatus == 11)
        write(2, "Segmentation fault\n", 19);
    else
        write(2, "Segmentation fault (core dumped)\n", 34);
    return (139);
}

int command_not_found(char *binary)
{
    char *str = my_strcat(my_strcat(binary, ":"), " Command not found.\n");

    write(2, str, my_strlen(str));
    return (1);
}

int wrong_arch(char *binary)
{
    char *str = my_strcat(my_strcat(binary, ":"), " Exec format error.");

    str = my_strcat(str, " Wrong Architecture.\n");
    write(2, str, my_strlen(str));
    return (1);
}

int perm_denied(char *binary)
{
    char *str = my_strcat(my_strcat(binary, ":"), " Permission denied.\n");

    write(2, str, my_strlen(str));
    return (1);
}

int failed_exec(char *binary, int err)
{
    if (err == 8)
        return wrong_arch(binary);
    if (err == 2)
        return (command_not_found(binary));
    return (0);
}
