/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** calc_size
*/

#include "corewar_header.h"

int calc_size_codingbyte(int byte)
{
    int nb1 = (byte / 1000000) % 100;
    int nb2 = (byte / 10000) % 100;
    int nb3 = (byte / 100) % 100;

    nb1 = (nb1 == 1 ? REG_SIZE : nb1);
    nb1 = (nb1 == 10 ? IND_SIZE : nb1);
    nb1 = (nb1 == 11 ? DIR_SIZE : nb1);
    nb2 = (nb2 == 1 ? REG_SIZE : nb2);
    nb2 = (nb2 == 10 ? IND_SIZE : nb2);
    nb2 = (nb2 == 11 ? DIR_SIZE : nb2);
    nb3 = (nb3 == 1 ? REG_SIZE : nb3);
    nb3 = (nb3 == 10 ? IND_SIZE : nb3);
    nb3 = (nb3 == 11 ? DIR_SIZE : nb3);
    return (nb1 + nb2 + nb3);
}
