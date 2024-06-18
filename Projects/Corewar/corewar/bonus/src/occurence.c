/*
** EPITECH PROJECT, 2024
** bonus
** File description:
** occurence
*/

#include "corewar_header.h"

static bool is_already_fill(int **result, int id)
{
    for (int i = 0; i < 4; i++) {
        if (result[i][0] == id)
            return (true);
    }
    return (false);
}

static int get_size_in_mem(map_t *vm, int id)
{
    int nb = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        if (vm->idmap[i] == id)
            nb++;
    }
    return (nb);
}

void get_biggest_prog(map_t *vm, int **result, int to_fill)
{
    int biggest_id = -1;
    int biggest_size = -1;

    for (int i = 0; i < vm->nb_prog; i++) {
        if (vm->programs[i] == NULL)
            continue;
        if (get_size_in_mem(vm, vm->programs[i]->id) > biggest_size && !is_already_fill(result, vm->programs[i]->id)) {
            biggest_id = vm->programs[i]->id;
            biggest_size = get_size_in_mem(vm, biggest_id);
        }
    }
    result[to_fill][0] = biggest_id;
    result[to_fill][1] = biggest_size;
}

int **occurence_winner(map_t *vm)
{
    int **result = malloc(sizeof(int *) * 4);

    for (int i = 0; i < 4; i++) {
        result[i] = malloc(sizeof(int) * 2);
        result[i][0] = -1;
        result[i][1] = -1;
    }
    for (int i = 0; i < 4; i++) {
        get_biggest_prog(vm, result, i);
    }
    return (result);
}
