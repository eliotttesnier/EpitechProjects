/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** fill_musics
*/

#include "rpg_header.h"

void fill_musics(gamedata_t *gamedata, config_t *config)
{
    gamedata->music = malloc(sizeof(music_t) * 1);
    gamedata->music->epic = sfMusic_createFromFile("assets/musics/epic.wav");
    if (gamedata->music->epic == NULL)
        exit(84);
    gamedata->music->menu = sfMusic_createFromFile("assets/musics/menu.wav");
    if (gamedata->music->menu == NULL)
        exit(84);
    gamedata->music->world = sfMusic_createFromFile("assets/musics/world.wav");
    if (gamedata->music->world == NULL)
        exit(84);
    sfMusic_setLoop(gamedata->music->menu, sfTrue);
    sfMusic_setLoop(gamedata->music->world, sfTrue);
    sfMusic_setLoop(gamedata->music->epic, sfTrue);
    (void)config;
}
