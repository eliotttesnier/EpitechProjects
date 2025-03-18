/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** ennemy_range
*/

#include "rpg_header.h"

sfVector2f get_center(sprite_t *sprite)
{
    sfFloatRect center = sfSprite_getGlobalBounds(sprite->sprite);

    return ((sfVector2f){center.left + center.width / 2,
        center.top + center.height / 2});
}

int get_range(ennemy_t *eny)
{
    if (strcmp("assets/sprites/ennemy/giant_golem(96x96).png", eny->path) == 0)
        return (50);
    if (strcmp("assets/sprites/ennemy/goblin(48x48).png", eny->path) == 0)
        return (35);
    if (strcmp("assets/sprites/ennemy/wolf(48x34).png", eny->path) == 0)
        return (40);
    return (30);
}

bool is_in_eny_range(gamedata_t *game, ennemy_t *eny)
{
    sfVector2f pCenter = get_center(game->entity->player->sprite);
    sfVector2f eCenter = get_center(eny->sprite);

    if (strcmp(eny->path, "assets/sprites/ennemy/giant_golem(96x96).png") == 0)
        eCenter.y += 30;
    if (sqrt(pow(pCenter.x - eCenter.x, 2) + pow(pCenter.y - eCenter.y, 2)) <
        get_range(eny))
        return (true);
    return (false);
}
