/*
** EPITECH PROJECT, 2023
** lower
** File description:
** returns a lower char
*/

#include <stdlib.h>
#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

char lower(char c)
{
    char upp[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 26; i++) {
        if (c == upp[i])
            return (upp[i] + 32);
    }
    return (c);
}
