/*
** EPITECH PROJECT, 2024
** n4s
** File description:
** output
*/

#include "header.h"

bool print_laps(char *line)
{
    if (strcmp(line, "Track Cleared") == 0)
        return (true);
    if (strcmp(line, "First CP Cleared") == 0)
        dprintf(2, "First Checkpoint Cleared !\n");
    if (strcmp(line, "CP Cleared") == 0)
        dprintf(2, "Checkpoint Cleared !\n");
    if (strcmp(line, "Lap Cleared") == 0)
        dprintf(2, "Lap Cleared !\n");
    return (false);
}

bool reached_end(char *line)
{
    char *buf = NULL;

    buf = strtok(line, ":\n");
    while (buf != NULL) {
        if (print_laps(buf) == true)
            return (true);
        buf = strtok(NULL, ":");
    }
    return (false);
}

char *get_output(void)
{
    size_t size = 0;
    char *line = NULL;

    getline(&line, &size, stdin);
    return (line);
}
