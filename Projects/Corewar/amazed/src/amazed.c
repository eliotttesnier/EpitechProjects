/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** amazed
*/

#include "header.h"

int error_cases(parsing_t *pars)
{
    if (pars == NULL)
        return (my_perror("Invalid script : Empty file.\n", -1));
    if (valid_nb_robots(pars->line) == -1)
        return (-1);
    mini_printf("#rooms\n");
    if (rooms_error(pars) == -1)
        return (-1);
    mini_printf("#tunnels\n");
    if (tunnels_error(pars) == -1)
        return (-1);
    mini_printf("#moves\n");
    return (0);
}

void free_lparsing(parsing_t *pars)
{
    if (pars == NULL)
        return;
    free_lparsing(pars->next);
    free(pars->line);
    free(pars);
}

static void free_lroom(rooms_t *rooms)
{
    if (rooms == NULL)
        return;
    free_lroom(rooms->next);
    free(rooms->id);
    free(rooms);
}

static void free_ltunnel(tunnels_t *tunnels)
{
    if (tunnels == NULL)
        return;
    free_ltunnel(tunnels->next);
    free(tunnels->id_1);
    free(tunnels->id_2);
    free(tunnels);
}

int amazed(int ac)
{
    parsing_t *pars = NULL;
    mapstat_t mapstat;

    if (ac != 1)
        return (my_perror("No arguments needed.\n", 84));
    fill_pars(&pars);
    if (error_cases(pars) == -1)
        return (84);
    filmap_tstat(pars, &mapstat);
    free_lparsing(pars);
    free_lroom(mapstat.rooms);
    free_ltunnel(mapstat.tunnels);
    return (0);
}
