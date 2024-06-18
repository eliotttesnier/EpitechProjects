/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** filmap_tstat
*/

#include "header.h"

void add_node_lrooms(parsing_t *pars, rooms_t **rooms)
{
    rooms_t *new = malloc(sizeof(rooms_t) * 1);
    rooms_t *tmp = *rooms;
    char **arr = str_to_array(pars->line, " -\t\n");

    new->id = my_strdup(arr[0]);
    new->x = my_getnbr(arr[1], 0);
    new->y = my_getnbr(arr[2], 0);
    new->room_type = ROOM;
    new->room_type = (pars->end == true ? END : new->room_type);
    new->room_type = (pars->start == true ? START : new->room_type);
    new->next = NULL;
    if (*rooms == NULL) {
        *rooms = new;
        free_arr(arr);
        return;
    }
    for (tmp = *rooms; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    free_arr(arr);
}

rooms_t *filrooms_t(parsing_t *pars)
{
    rooms_t *new = NULL;
    parsing_t *tmp = pars;

    while (tmp != NULL) {
        if (words_number(tmp->line) == 2)
            break;
        if (!is_start(tmp) && !is_end(tmp) && tmp->ignore == false)
            add_node_lrooms(tmp, &new);
        tmp = tmp->next;
    }
    return (new);
}

void add_node_ltunnel(parsing_t *pars, tunnels_t **tunnels)
{
    tunnels_t *new = malloc(sizeof(tunnels_t) * 1);
    tunnels_t *tmp = *tunnels;
    char **arr = str_to_array(pars->line, " -\t\n");

    new->id_1 = my_strdup(arr[0]);
    new->id_2 = my_strdup(arr[1]);
    new->next = NULL;
    if (*tunnels == NULL) {
        *tunnels = new;
        free_arr(arr);
        return;
    }
    for (tmp = *tunnels; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new;
    free_arr(arr);
}

tunnels_t *filtunnels_t(parsing_t *pars)
{
    tunnels_t *new = NULL;
    parsing_t *tmp = pars;

    while (tmp != NULL) {
        if (tmp->ignore == false)
            add_node_ltunnel(tmp, &new);
        tmp = tmp->next;
    }
    return (new);
}

void filmap_tstat(parsing_t *pars, mapstat_t *mapstat)
{
    mapstat->nb_robots = my_getnbr(pars->line, 0);
    mapstat->rooms = filrooms_t(pars->next);
    mapstat->tunnels = filtunnels_t(get_first_tunnel(pars));
}
