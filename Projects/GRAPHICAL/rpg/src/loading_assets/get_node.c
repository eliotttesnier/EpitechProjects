/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** get_node
*/

#include "rpg_header.h"

config_t *get_node(char *id, config_t *config)
{
    config_t *tmp = config;

    while (tmp != NULL) {
        if (strcmp(tmp->line[0], id) == 0)
            break;
        tmp = tmp->next;
    }
    return (tmp);
}
