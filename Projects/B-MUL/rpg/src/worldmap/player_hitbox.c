/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** player_hitbox
*/

#include "rpg_header.h"

sfColor col_color(float x, float y, gamedata_t *game)
{
    if (x < 0 || x >= 6400)
        return (sfBlack);
    if (y < 0 || y >= 6432)
        return (sfBlack);
    return (sfImage_getPixel(game->map->colmap, (int)x, (int)y));
}

static bool check_bridge(sfColor tmp, gamedata_t *game)
{
    if (game->obj->bridge->repaired == false)
        return (true);
    if (tmp.r == 255)
        return (false);
    return (true);
}

static bool check_mine(sfColor tmp, gamedata_t *game)
{
    if (game->adv < KILL_GOLEM)
        return (true);
    if (tmp.b == 255)
        return (false);
    return (true);
}

bool check_walls(gamedata_t *game)
{
    player_t *p = game->entity->player;
    static float bef = 0;
    float time = sfClock_getElapsedTime(p->movement->clock).microseconds;
    float x = p->position.x + p->movement->direction.x * (time - bef) / SPEED;
    float y = p->position.y;
    sfColor tmp = col_color(x, y + 10, game);

    bef = time;
    if (tmp.a >= 200 && check_bridge(tmp, game) && check_mine(tmp, game))
        return (true);
    tmp = col_color(x + 15, y + 10, game);
    if (tmp.a >= 200 && check_bridge(tmp, game) && check_mine(tmp, game))
        return (true);
    tmp = col_color(x, y + 23, game);
    if (tmp.a >= 200 && check_bridge(tmp, game) && check_mine(tmp, game))
        return (true);
    tmp = col_color(x + 15, y + 23, game);
    if (tmp.a >= 200 && check_bridge(tmp, game) && check_mine(tmp, game))
        return (true);
    return (check_entity(game, x, y));
}

bool check_height(gamedata_t *game)
{
    player_t *p = game->entity->player;
    static float bef = 0;
    float time = sfClock_getElapsedTime(p->movement->clock).microseconds;
    float y = p->position.y + p->movement->direction.y * (time - bef) / SPEED;
    float x = p->position.x;
    sfColor tmp = col_color(x, y + 10, game);

    bef = time;
    if (tmp.a >= 200 && check_bridge(tmp, game) && check_mine(tmp, game))
        return (true);
    tmp = col_color(x + 15, y + 10, game);
    if (tmp.a >= 200 && check_bridge(tmp, game) && check_mine(tmp, game))
        return (true);
    tmp = col_color(x, y + 23, game);
    if (tmp.a >= 200 && check_bridge(tmp, game) && check_mine(tmp, game))
        return (true);
    tmp = col_color(x + 15, y + 23, game);
    if (tmp.a >= 200 && check_bridge(tmp, game) && check_mine(tmp, game))
        return (true);
    return (check_entity(game, x, y));
}
