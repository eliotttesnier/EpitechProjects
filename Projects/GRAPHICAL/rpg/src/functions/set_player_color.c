/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** set_player_color
*/

#include "rpg_header.h"

void set_player_sprites_color(player_t *player, sfColor color)
{
    for (int i = 0; i < 4; i++) {
        sfSprite_setColor(player->sprite[i].sprite, color);
    }
    for (int i = 0; i < 3; i++) {
        sfSprite_setColor(player->attack[i].sprite, color);
    }
}

void set_player_color(gamedata_t *game, bool red)
{
    sfColor color = sfSprite_getColor(game->entity->player->sprite[0].sprite);

    if (red) {
        set_player_sprites_color(game->entity->player, sfRed);
        return;
    }
    if (color.b < 254)
        color.b += 2;
    if (color.g < 254)
        color.g += 2;
    set_player_sprites_color(game->entity->player, color);
}
