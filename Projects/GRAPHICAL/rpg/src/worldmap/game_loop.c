/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** game_loop
*/

#include "rpg_header.h"

static void set_white_eny(gamedata_t *game)
{
    ennemy_t *eny = game->entity->ennemy;
    sfColor color;

    for (; eny != NULL; eny = eny->next) {
        if (eny->alive == false)
            continue;
        if (!is_eny_visible(game, eny))
            continue;
        color = sfSprite_getColor(eny->sprite->sprite);
        if (color.g < 254)
            color.g += 2;
        if (color.b < 254)
            color.b += 2;
        sfSprite_setColor(eny->sprite->sprite, color);
    }
}

void game_loop(gamedata_t *gamedata, sfEvent *event)
{
    if (sfMusic_getStatus(gamedata->music->world) == sfStopped)
        sfMusic_play(gamedata->music->world);
    set_white_eny(gamedata);
    world_events(gamedata, event);
    game_process(gamedata);
    player_anim(gamedata->entity->player);
    pnj_anim(gamedata);
    eny_anim(gamedata);
    chest_anim(gamedata);
    update_text(gamedata);
    game_display(gamedata, false);
}
