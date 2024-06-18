/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** inventory_loop
*/

#include "rpg_header.h"

void inventory_loop(gamedata_t *game, sfEvent *event)
{
    game->entity->player->movement->direction = (sfVector2f){0, 0};
    update_position(game);
    update_text(game);
    inventory_positions(game);
    inventory_event(game, event);
    game_display(game, true);
    inventory_display(game);
}
