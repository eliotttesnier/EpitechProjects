/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** over_loop
*/

#include "rpg_header.h"

void set_gameover_position(gamedata_t *game)
{
    sfVector2f pos = sfView_getCenter(game->window->view);

    pos.x -= 1920 / 4 / 2;
    pos.y -= 1080 / 4 / 2;
    sfSprite_setPosition(game->hud->gameover->sprite, pos);
}

void over_loop(gamedata_t *game, sfEvent *event)
{
    game->entity->player->movement->direction = (sfVector2f){0, 0};
    update_position(game);
    if (sfMusic_getStatus(game->music->world) == sfPlaying)
        sfMusic_stop(game->music->world);
    while (sfRenderWindow_pollEvent(game->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(game->window->window);
        if (event->type == sfEvtKeyReleased) {
            game->scene = S_GAME;
            load(game, false);
        }
    }
    set_gameover_position(game);
    over_display(game);
}
