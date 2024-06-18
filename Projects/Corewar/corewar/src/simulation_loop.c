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

static void find_last_player(map_t *vm)
{
    if (get_alive_player(vm, false) == 0) {
        mini_printf("The player 0() has won.\n");
        return;
    }
    for (int i = 0; i < vm->nb_prog; i++) {
        if (vm->programs[i] != NULL) {
            mini_printf("The player %d(", vm->programs[i]->id);
            mini_printf("%s) has won.\n", vm->programs[i]->name);
        }
    }
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

void execute_closed_loop(map_t *vm)
{
    int cycle_to_die = CYCLE_TO_DIE;

    for (int i = 1; i <= cycle_to_die; i++) {
        exec_programs(vm);
        if (vm->nb_live >= 40) {
            vm->nb_live = 0;
            cycle_to_die -= CYCLE_DELTA;
        }
        if (i >= cycle_to_die && get_alive_player(vm, true) > 1) {
            remove_alive(vm);
            i = 0;
        }
        vm->cycle--;
        if (vm->cycle == 0)
            break;
    }
    if (get_alive_player(vm, false) > 1)
        display_mem(vm);
    else
        find_last_player(vm);
}

void simulate_loop(map_t *vm)
{
    int cycle_to_die = CYCLE_TO_DIE;

    if (vm->cycle != -1) {
        execute_closed_loop(vm);
        return;
    }
    for (int i = 1; i <= cycle_to_die; i++) {
        exec_programs(vm);
        if (vm->nb_live >= 40) {
            vm->nb_live = 0;
            cycle_to_die -= CYCLE_DELTA;
        }
        if (i >= cycle_to_die && get_alive_player(vm, true) > 1) {
            remove_alive(vm);
            i = 0;
        }
    }
    find_last_player(vm);
}
