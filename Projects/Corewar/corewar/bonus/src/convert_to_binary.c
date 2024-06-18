/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** convert_to_binary
*/

#include "corewar_header.h"

int convert_to_binary(char bytecode)
{
    int new = 0;

    for (int i = 0; i < 8; i++) {
        new *= 10;
        new += ((bytecode & 10000000) == 0 ? 0 : 1);
        bytecode = bytecode << 1;
    }
    return (new);
}
