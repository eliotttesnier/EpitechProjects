/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** remove_com
*/

#include "header.h"

void remove_coms(char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\t')
            line[i] = ' ';
        if (line[i] == '#') {
            line[i] = '\n';
            line[i + 1] = '\0';
        }
        if (line[i] == '\n')
            break;
    }
}
