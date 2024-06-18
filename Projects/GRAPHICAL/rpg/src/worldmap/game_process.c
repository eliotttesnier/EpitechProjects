/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** game_process
*/

#include "rpg_header.h"

void set_positions(player_t *player)
{
    for (int i = 0; i < 4; i++) {
        sfSprite_setPosition(player->sprite[i].sprite, player->position);
    }
    for (int i = 0; i < 3; i++) {
        sfSprite_setPosition(player->attack[i].sprite, player->position);
    }
}

void update_position(gamedata_t *game)
{
    player_t *player = game->entity->player;
    sfVector2f direction = player->movement->direction;
    float time = sfClock_getElapsedTime(player->movement->clock).microseconds;
    static float last_time = 0;

    if (player->fight->attacking == true) {
        last_time = time;
        return;
    }
    if (direction.x != 0 && direction.y != 0)
        direction = (sfVector2f){direction.x / 1.45, direction.y / 1.45};
    if (!check_walls(game))
        player->position.x += direction.x * (time - last_time) / SPEED;
    if (!check_height(game))
        player->position.y += direction.y * (time - last_time) / SPEED;
    last_time = time;
    set_positions(player);
}

void update_view(gamedata_t *game)
{
    static bool first_time = true;
    sfVector2f center = sfView_getCenter(game->window->view);
    sfVector2f pos = game->entity->player->position;

    if (first_time == true)
        center = pos;
    first_time = false;
    if (pos.x > 480 / 2 && pos.x < 6400 - (480 / 2))
        sfView_setCenter(game->window->view, (sfVector2f){pos.x, center.y});
    center = sfView_getCenter(game->window->view);
    if (pos.y > 300 / 2 && pos.y < 6432 - (300 / 2))
        sfView_setCenter(game->window->view, (sfVector2f){center.x, pos.y});
    sfView_setSize(game->window->view,
        (sfVector2f){1920 / 4, 1080 / 4});
    sfRenderWindow_setView(game->window->window, game->window->view);
}

static void stop_popup(gamedata_t *game)
{
    float time = 0;
    sfClock *clock = game->hud->popup->time_since_display;

    if (game->hud->popup->msg == NULL)
        return;
    time = sfClock_getElapsedTime(clock).microseconds;
    if (time > 3000000) {
        free(game->hud->popup->msg);
        game->hud->popup->msg = NULL;
    }
}

void game_process(gamedata_t *game)
{
    process_adv(game);
    update_position(game);
    update_entity_pos(game);
    update_view(game);
    check_attack(game);
    stop_popup(game);
    revive_ennemy(game);
    ennemy_attack(game);
    if (game->inventory->stats->health <= 0) {
        play_sfx(game, SFX_DIE);
        game->scene = S_GAME_OVER;
        game->prescene = S_GAME;
    }
}
