/*
** EPITECH PROJECT, 2024
** NAVY
** File description:
** check_file
*/

#include "../include/navy_header.h"

int check_crossing(char *buff)
{
    char **map = create_map(buff);
    int total = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            total += map[i][j];
        }
    }
    if (total != 3026)
        return (84);
    game_stat->my_map = map;
    game_stat->opp_map = create_opp_map();
    return (0);
}

int check_position(char *buff)
{
    for (int i = 0; i < 25; i += 8) {
        if (buff[i] - 48 != (i / 8 + 2))
            return (84);
        if ((buff[i + 2] - 65) >= 8 || (buff[i + 5] - 65) >= 8)
            return (84);
        if ((buff[i + 3] - 48) % 9 == 0 || (buff[i + 6] - 48) % 9 == 0)
            return (84);
        if ((buff[i + 2] != buff[i + 5]) && (buff[i + 3] != buff[i + 6]))
            return (84);
    }
    if (check_crossing(buff) == 84)
        return (84);
    return (0);
}

int check_file(char *filepath)
{
    int check = 0;
    int fd = open(filepath, O_RDONLY);
    char buff[33];

    read(fd, buff, 32);
    buff[32] = '\0';
    for (int i = 0; i < 25; i += 8) {
        if (IS_UCASE(buff[i + 2]) == 0 || IS_UCASE(buff[i + 5]) == 0)
            return (84);
        if (IS_NBR(buff[i]) == 0 || IS_NBR(buff[i + 3]) == 0 ||
            IS_NBR(buff[i + 6]) == 0)
            return (84);
        if (buff[i + 1] != ':' || buff[i + 4] != ':' || buff[i + 7] != '\n')
            return (84);
    }
    if (check_position(buff) == 84)
        return (84);
    return (0);
}
