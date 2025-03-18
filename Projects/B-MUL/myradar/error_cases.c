/*
** EPITECH PROJECT, 2023
** error_cases.c
** File description:
** error cases
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"

int scan_file(char *file)
{
    int buffsiz = get_size(file);
    int file_desc = open(file, O_RDONLY);
    char *buff = malloc(buffsiz + 5);

    read(file_desc, buff, buffsiz);
    buff[buffsiz] = '\0';
    if (buff[0] != 'A' && buff[0] != 'T')
        return (84);
    for (int i = 0; buff[i] != '\0'; i++) {
        if (buff[i] != 'A' && buff[i] != 'T' && buff[i] != ' ' &&
        buff[i] != '\n' && (buff[i] < '0' || buff[i] > '9'))
            return (84);
    }
    for (int i = 1; buff[i] != '\0'; i++) {
        if (((buff[i] == 'A' || buff[i] == 'T') && buff[i + 1] != ' ') ||
            (i == 1 && buff[i] != ' ') || buff[i] == ' ' && buff[i + 1] == ' ')
            return (84);
        if (buff[i - 1] == '\n' && buff[i] != 'A' && buff[i] != 'T')
            return (84);
    }
}

int error_cases(char *file)
{
    struct stat sb;

    if (stat(file, &sb) == -1) {
        write(2, "Error : file doesn't exist\n", 28);
        return (84);
    }
    if (S_ISDIR(sb.st_mode)) {
        write(2, "Error : Is a directory\n", 24);
        return (84);
    }
    if (scan_file(file) == 84) {
        write(2, "Error : invalid script\n", 24);
        return (84);
    }
    return (0);
}
