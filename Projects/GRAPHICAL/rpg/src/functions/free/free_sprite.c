/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_sprite
*/

#include "rpg_header.h"

void free_sprite_l(sprite_t sprite)
{
    sfSprite_destroy(sprite.sprite);
    sfTexture_destroy(sprite.texture);
}

void free_sprite(sprite_t *sprite)
{
    sfSprite_destroy(sprite->sprite);
    sfTexture_destroy(sprite->texture);
    free(sprite);
}
