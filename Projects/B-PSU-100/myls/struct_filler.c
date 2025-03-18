/*
** EPITECH PROJECT, 2023
** struct_filler
** File description:
** used to fill the struct
*/

#include "struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "myprintf/include/my.h"

void is_mod_filler(struct mods *modifiers, char **av, int i)
{
    int len_mods = pfmy_strlen(av[i]);

    for (int j = 0; j < len_mods; j++) {
        if (av[i][j] == 'a')
            modifiers->a = 1;
        if (av[i][j] == 'l')
            modifiers->l = 1;
        if (av[i][j] == 'R')
            modifiers->R = 1;
        if (av[i][j] == 'd')
            modifiers->d = 1;
        if (av[i][j] == 'r')
            modifiers->r = 1;
        if (av[i][j] == 't')
            modifiers->t = 1;
    }
}

void fill_struct(struct mods *modifiers, char **av, int ac)
{
    *modifiers = (struct mods){0, 0, 0, 0, 0, 0};
    for (int i = 0; i < ac; i++) {
        if (av[i][0] == '-')
            is_mod_filler(modifiers, av, i);
    }
}
