/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** display_mem
*/

#include "corewar_header.h"

void print_hexa(unsigned char nbr)
{
    char hex_base[] = "0123456789ABCDEF";
    int st = 0;
    int nd = 0;

    for (int i = 1; i < nbr; i++) {
        nd++;
        if (nd > 15) {
            st++;
            nd = 0;
        }
    }
    mini_printf("%c%c", hex_base[st], hex_base[nd]);
}

void display_mem(map_t *vm)
{
    for (int i = 0; i < MEM_SIZE; i += 32) {
        for (int j = 0; j < 32; j++) {
            mini_printf("%c", (j == 0 ? '\0' : ' '));
            print_hexa(vm->map[i + j]);
        }
        mini_printf("\n");
    }
}
