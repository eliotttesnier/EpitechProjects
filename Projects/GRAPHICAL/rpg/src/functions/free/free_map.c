/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_map
*/

#include "rpg_header.h"

void free_map(map_t *map)
{
    sfImage_destroy(map->colmap);
    free_sprite(map->back);
    free_sprite(map->dec);
    free(map);
}
