/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** world_event
*/

#include "rpg_header.h"

void manage_key_pressed(gamedata_t *game, sfEvent *event)
{
    if (event->key.code == game->settings->keys[INVENTORY]) {
        game->scene = S_INVENTORY;
        game->prescene = S_GAME;
    }
    if (event->key.code == sfKeyEscape) {
        game->scene = S_PAUSE_MENU;
        game->prescene = S_GAME;
    }
    if (event->key.code == game->settings->keys[ATTACK] &&
        game->inventory->equipment->equiped[WEAPON] != NULL)
        player_attack(game);
    if (event->key.code == game->settings->keys[INTERACT])
        interact(game);
    if (event->key.code == sfKeyM)
        game->entity->player->position = (sfVector2f){4420, 5560};
    if (event->key.code == sfKeyUp)
        game->adv += 1;
    if (event->key.code == sfKeyDown)
        game->adv -= 1;
}

void manage_player_direction(gamedata_t *game)
{
    if (game->entity->player->fight->attacking == true)
        return;
    game->entity->player->movement->direction.x = 0;
    game->entity->player->movement->direction.y = 0;
    if (sfKeyboard_isKeyPressed(game->settings->keys[FORWARD]))
        game->entity->player->movement->direction.y -= 1;
    if (sfKeyboard_isKeyPressed(game->settings->keys[BACKWARD]))
        game->entity->player->movement->direction.y += 1;
    if (sfKeyboard_isKeyPressed(game->settings->keys[LEFT]))
        game->entity->player->movement->direction.x -= 1;
    if (sfKeyboard_isKeyPressed(game->settings->keys[RIGHT]))
        game->entity->player->movement->direction.x += 1;
}

void world_events(gamedata_t *game, sfEvent *event)
{
    manage_player_direction(game);
    while (sfRenderWindow_pollEvent(game->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(game->window->window);
        if (event->type == sfEvtKeyPressed)
            manage_key_pressed(game, event);
    }
}
