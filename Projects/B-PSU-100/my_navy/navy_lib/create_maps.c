/*
** EPITECH PROJECT, 2024
** NAVY
** File description:
** create maps
*/

#include "../include/navy_header.h"

char **create_opp_map(void)
{
    char **map = malloc(sizeof(char *) * 9);

    for (int i = 0; i < 8; i++) {
        map[i] = malloc(sizeof(char) * 9);
        for (int j = 0; j < 8; j++) {
            map[i][j] = '.';
        }
    }
    return (map);
}

char **create_map(char *buff)
{
    char **map = malloc(sizeof(char *) * 9);

    for (int i = 0; i < 8; i ++) {
        map[i] = malloc(sizeof(char) * 9);
        for (int j = 0; j < 8; j++) {
            map[i][j] = '.';
        }
    }
    for (int i = 0; i < 25; i += 8) {
        map[buff[i + 3] - 49][buff[i + 2] - 65] = i / 8 + 2 + 48;
        for (int a = buff[i + 2] - 65; a < buff[i + 5] - 65; a++) {
            map[buff[i + 3] - 49][a] = i / 8 + 2 + 48;
        }
        for (int a = buff[i + 3] - 49; a < buff[i + 6] - 49; a++) {
            map[a][buff[i + 2] - 65] = i / 8 + 2 + 48;
        }
        map[buff[i + 6] - 49][buff[i + 5] - 65] = i / 8 + 2 + 48;
    }
    return (map);
}
