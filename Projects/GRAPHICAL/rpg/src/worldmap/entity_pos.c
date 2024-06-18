/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** entity_pos
*/

#include "rpg_header.h"

void actulise_dir_ennemy(gamedata_t *game, ennemy_t *eny)
{
    sfVector2f pos = game->entity->player->position;
    sfVector2f epos = eny->position;

    pos.x += 7.5;
    pos.y += 12;
    epos.x += (eny->sprite->rect.width / 2);
    epos.y += (eny->sprite->rect.height / 2);
    eny->movement->direction.x = 0;
    eny->movement->direction.y = 0;
    if (abs((int)(pos.x - epos.x)) <= (eny->sprite->rect.width) * 0.75 &&
        abs((int)(pos.y - epos.y)) <= (eny->sprite->rect.height) * 0.75)
        return;
    if (pos.x - epos.x > 10)
        eny->movement->direction.x = 1;
    else if (pos.x - epos.x < -10)
        eny->movement->direction.x = -1;
    if (pos.y - epos.y > 10)
        eny->movement->direction.y = 1;
    else if (pos.y - epos.y < -10)
        eny->movement->direction.y = -1;
}

void move_ennemy(ennemy_t *eny)
{
    float time = sfClock_getElapsedTime(eny->movement->clock).microseconds;
    static float last_time = 0;
    sfVector2f direction = eny->movement->direction;
    sfVector2f pos = eny->position;

    if (sqrt(pow(eny->position.x - eny->anchor.x, 2) +
        pow(eny->position.y - eny->anchor.y, 2)) > 500) {
        eny->position.x = eny->anchor.x + (pos.x - eny->anchor.x) * 0.99;
        eny->position.y = eny->anchor.y + (pos.y - eny->anchor.y) * 0.99;
        return;
    }
    if (direction.x != 0 && direction.y != 0)
        direction = (sfVector2f){direction.x / 1.45, direction.y / 1.45};
    eny->position.x += (direction.x == 0 ? 0 : (direction.x / 2)) *
        (time - last_time) / 500.0;
    eny->position.y += (direction.y == 0 ? 0 : (direction.y / 2)) *
        (time - last_time) / 500.0;
    sfSprite_setPosition(eny->sprite->sprite, eny->position);
    last_time = time;
}

void update_entity_pos(gamedata_t *game)
{
    for (ennemy_t *eny = game->entity->ennemy; eny != NULL; eny = eny->next) {
        actulise_dir_ennemy(game, eny);
        if (!is_eny_visible(game, eny) || !eny->alive)
            eny->movement->direction = (sfVector2f){0, 0};
        move_ennemy(eny);
    }
}
