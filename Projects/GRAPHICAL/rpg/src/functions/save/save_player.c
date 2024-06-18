/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** save_player
*/

#include "rpg_header.h"

void save_player(gamedata_t *game, int fd)
{
    player_t *player = game->entity->player;
    stats_t *st = game->inventory->stats;

    dprintf(fd, "PLAYER:");
    dprintf(fd, "%i;%i", (int)player->position.x, (int)player->position.y);
    dprintf(fd, ";%i;%i;%i;%i;%i\n",
        st->health, st->attack, st->defense, st->xp, st->mana);
}
