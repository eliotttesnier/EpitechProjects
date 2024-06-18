/*
** EPITECH PROJECT, 2024
** NAVY
** File description:
** check_input
*/

#include "../include/navy_header.h"

int check_input(char *input)
{
    int x = 0;
    int y = 0;

    if (input[2] != '\n')
        return (0);
    if (IS_UCASE(input[0]) == 0 || IS_NBR(input[1] == 0))
        return (0);
    x = input[0] - 65;
    y = input[1] - 49;
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return (0);
    return (1);
}
