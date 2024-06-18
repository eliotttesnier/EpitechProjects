/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_gamedata
*/

#include "rpg_header.h"

void free_gamedata(gamedata_t *game, bool load)
{
    free_entity(game->entity);
    free_inventory(game->inventory);
    free_map(game->map);
    free_music(game->music);
    free_settings(game->settings);
    free_obj(game->obj);
    free_sfx(game->sfx);
    free_menu(game->menu);
    if (!load) {
        free_window(game->window);
        free(game);
    }
}
