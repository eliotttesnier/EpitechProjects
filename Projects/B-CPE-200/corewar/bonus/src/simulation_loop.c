/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** simulation_loop
*/

#include "corewar_header.h"

static void del_warrior(map_t *vm, int i, prog_t *to_del)
{
    if (vm->programs[i] == to_del) {
        vm->programs[i] = vm->programs[i]->next;
        return;
    }
    for (prog_t *tmp = vm->programs[i]; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->next == to_del)
            tmp->next = tmp->next->next;
    }
}

int check_dead_warriors(map_t *vm, int i, bool test)
{
    prog_t *tmp = vm->programs[i];
    int nb = 0;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->alive)
            nb += 1;
        if (!tmp->alive && test)
            del_warrior(vm, i, tmp);
    }
    return (nb > 0 ? 1 : 0);
}

int get_alive_player(map_t *vm, bool test)
{
    int nb_alive = 0;

    for (int i = 0; i < vm->nb_prog; i++) {
        if (vm->programs[i] == NULL)
            continue;
        nb_alive += check_dead_warriors(vm, i, test);
    }
    return (nb_alive);
}

static void remove_alive(map_t *vm)
{
    prog_t *tmp;

    for (int i = 0; i < vm->nb_prog; i++) {
        if (vm->programs[i] == NULL)
            continue;
        for (tmp = vm->programs[i]; tmp != NULL; tmp = tmp->next) {
            tmp->alive = false;
        }
    }
}

void execute_area_loop(map_t *vm)
{
    int **tmp = occurence_winner(vm);

    for (int i = 0; i < vm->cycle; i++) {
        exec_programs(vm);
        erase();
        display_area_mem(vm, i, vm->cycle);
        refresh();
        usleep(10000);
    }
    if (tmp[0][1] == tmp[1][1])
        display_cw_winner(vm, true, true);
    else
        display_cw_winner(vm, true, false);
    endwin();
}

void simulate_loop(map_t *vm)
{
    int cycle_to_die = CYCLE_TO_DIE;
    sfMusic *intro = sfMusic_createFromFile("intro.wav");
    sfMusic *theme = sfMusic_createFromFile("valkyrie.wav");

    initscr();
    start_color();
    curs_set(0);
    sfMusic_play(intro);
    display_intro();
    sfMusic_play(theme);
    if (vm->cycle != -1) {
        execute_area_loop(vm);
        return;
    }
    for (int i = 1; i <= cycle_to_die; i++) {
        exec_programs(vm);
        erase();
        display_nc_mem(vm, i, cycle_to_die);
        refresh();
        usleep(10000);
        if (vm->nb_live >= 40) {
            vm->nb_live = 0;
            cycle_to_die -= CYCLE_DELTA;
        }
        if (i >= cycle_to_die && get_alive_player(vm, true) > 1) {
            remove_alive(vm);
            i = 0;
        }
    }
    display_cw_winner(vm, false, false);
    endwin();
}
