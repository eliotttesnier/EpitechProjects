/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_music
*/

#include "rpg_header.h"

void free_music(music_t *music)
{
    sfMusic_stop(music->epic);
    sfMusic_destroy(music->epic);
    sfMusic_stop(music->world);
    sfMusic_destroy(music->world);
    sfMusic_stop(music->menu);
    sfMusic_destroy(music->menu);
    free(music);
}
