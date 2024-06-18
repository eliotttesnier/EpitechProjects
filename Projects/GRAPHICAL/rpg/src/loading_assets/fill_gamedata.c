/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** fill_gamedata
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
    fill_settings,
    fill_musics,
    fill_object_list,
    fill_startmenu,
    fill_optionmenu,
    fill_gamemenu,
    fill_game_hud,
};

void free_config(config_t *config)
{
    if (config == NULL)
        free_config(config->next);
    for (int i = 0; config->line[i] != NULL; i++) {
        free(config->line[i]);
    }
    free(config->line);
    free(config);
}

void fill_gamedata(gamedata_t *gamedata)
{
    int fd = open("./files/config.txt", O_RDONLY);
    static int load = 0;
    config_t *conf;

    close(fd);
    if (load > 14)
        return;
    conf = get_config("./files/config.txt");
    load_func[load](gamedata, conf);
    load++;
    free_config(conf);
}
