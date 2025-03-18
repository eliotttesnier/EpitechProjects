/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** play_sfx
*/

#include "rpg_header.h"

void play_sfx(gamedata_t *game, sfx_enum_t sfx)
{
    sfMusic_stop(game->sfx->sounds[sfx]);
    sfMusic_play(game->sfx->sounds[sfx]);
}
