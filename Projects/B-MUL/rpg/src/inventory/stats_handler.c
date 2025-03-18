/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** stats_handler
*/

#include "rpg_header.h"

void remove_stats(gamedata_t *game, item_t *item)
{
    game->inventory->stats->defense -= item->def;
    game->inventory->stats->attack -= item->atk;
}

void add_stats(gamedata_t *game, item_t *item)
{
    game->inventory->stats->defense += item->def;
    game->inventory->stats->attack += item->atk;
}
