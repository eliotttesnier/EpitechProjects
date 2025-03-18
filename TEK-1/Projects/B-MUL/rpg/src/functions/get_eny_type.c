/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** get_eny_type
*/

#include "rpg_header.h"

eny_t get_eny_type(ennemy_t *eny)
{
    if (strcmp("assets/sprites/ennemy/giant_golem(96x96).png", eny->path) == 0)
        return (GOLEM);
    if (strcmp("assets/sprites/ennemy/goblin(48x48).png", eny->path) == 0)
        return (GOBLIN);
    if (strcmp("assets/sprites/ennemy/wolf(48x34).png", eny->path) == 0)
        return (WOLF);
    return (GOBLIN);
}
