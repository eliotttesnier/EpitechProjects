/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** get_eny_hitbox
*/

#include "rpg_header.h"

static sfFloatRect get_goblin_hitbox(sfFloatRect rect)
{
    rect.top += 32;
    rect.height -= 32;
    rect.left += 15;
    rect.width -= 30;
    return (rect);
}

static sfFloatRect get_wolf_hitbox(sfFloatRect rect)
{
    rect.top += 10;
    rect.height -= 10;
    rect.left += 10;
    rect.width -= 20;
    return (rect);
}

static sfFloatRect get_ggolem_hitbox(sfFloatRect rect)
{
    rect.top += 65;
    rect.height -= 65;
    rect.left += 30;
    rect.width -= 60;
    return (rect);
}

sfFloatRect get_eny_hitbox(ennemy_t *eny)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(eny->sprite->sprite);

    if (strcmp(eny->path, "assets/sprites/ennemy/goblin(48x48).png") == 0)
        return (get_goblin_hitbox(rect));
    if (strcmp(eny->path, "assets/sprites/ennemy/wolf(48x34).png") == 0)
        return (get_wolf_hitbox(rect));
    if (strcmp(eny->path, "assets/sprites/ennemy/giant_golem(96x96).png") == 0)
        return (get_ggolem_hitbox(rect));
    return (rect);
}
