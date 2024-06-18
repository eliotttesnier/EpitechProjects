/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** get_eny_hitbox
*/

#include "rpg_header.h"

int my_nbrlen(int nbr)
{
    int i = 0;

    if (nbr == 0)
        return (1);
    for (; nbr > 0; i++) {
        nbr /= 10;
    }
    return (i);
}

char *my_itoa(int nbr)
{
    int len = my_nbrlen(nbr);
    char *new = malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; i++) {
        new[i] = 48 + ((nbr / (int)pow(10, len - 1 - i)) % 10);
    }
    new[len] = '\0';
    return (new);
}
