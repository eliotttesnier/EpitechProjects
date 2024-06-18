/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_sfx
*/

#include "rpg_header.h"

void free_sfx(sfx_t *sfx)
{
    for (int i = 0; i < NB_SFX; i++) {
        sfMusic_destroy(sfx->sounds[i]);
    }
    free(sfx);
}
