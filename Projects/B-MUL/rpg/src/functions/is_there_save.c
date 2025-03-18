/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** is_there_save
*/

#include "rpg_header.h"

bool is_there_save(void)
{
    int fd = open("files/save.txt", O_RDONLY);

    if (fd == -1)
        return (false);
    close(fd);
    return (true);
}
