/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** load
*/

#include "rpg_header.h"

static const load_func_t load_func[15] = {
    fill_backpack,
    fill_equipment,
    fill_skilltree,
    fill_maps,
    fill_player,
    fill_preview,
    fill_pnj_list,
    fill_ennemy_list,
    fill_musics,
    fill_settings,
    fill_object_list,
    fill_startmenu,
    fill_optionmenu,
    fill_gamemenu,
    fill_game_hud,
};

void load(gamedata_t *game, bool new)
{
    config_t *config = get_config("files/save.txt");

    if (new == true)
        config = get_config("files/config.txt");
    if (config == NULL) {
        exit(84);
    }
    free_gamedata(game, true);
    for (int i = 0; i < 15; i++) {
        load_func[i](game, config);
    }
}
