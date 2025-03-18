/*
** EPITECH PROJECT, 2024
** bonus
** File description:
** display_area_mem
*/

#include "corewar_header.h"

int get_size_in_mem(map_t *vm, int id)
{
    int nb = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        if (vm->idmap[i] == id)
            nb++;
    }
    return (nb);
}

static int get_color(map_t *vm, int pos)
{
    for (int i = 0; i < vm->nb_prog; i++) {
        if (vm->programs[i] == NULL)
            continue;
        for (prog_t *tmp = vm->programs[i]; tmp != NULL; tmp = tmp->next) {
            if (pos == tmp->pc)
                return (8 + i);
        }
        if (vm->idmap[pos] == vm->programs[i]->id)
            return (4 + i);
    }
    return (1);
}

void display_area_mem(map_t *vm, int cycle, int max_cycle)
{
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(7, COLOR_BLACK, COLOR_CYAN);
    init_pair(8, COLOR_BLUE, COLOR_WHITE);
    init_pair(9, COLOR_YELLOW, COLOR_WHITE);
    init_pair(10, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(11, COLOR_CYAN, COLOR_WHITE);

    attron(COLOR_PAIR(1));
    printw("\n\n");
    for (int i = 0; i < vm->nb_prog; i++) {
        attron(COLOR_PAIR(1));
        if (vm->programs[i] == NULL)
            continue;
        printw("         %s: ", vm->programs[i]->name);
        attron(COLOR_PAIR(4 + i));
        printw("%d", get_size_in_mem(vm, vm->programs[i]->id));
    }
    attron(COLOR_PAIR(1));
    printw("\n\n\n         number of cycles: %4d / %4d\n", cycle, max_cycle);

    for (int i = 0; i < MEM_SIZE; i++) {
        attron(COLOR_PAIR(1));
        if (i % 110 == 0) {
            printw("\n");
            printw("         ");
        }
        attron(COLOR_PAIR(get_color(vm, i)));
        printw("%02X", vm->map[i]);
    }
    printw("\n");
}