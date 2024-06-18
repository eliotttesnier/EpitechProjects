/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_animation
*/

#include "rpg_header.h"

void free_animation(animation_t *anim)
{
    sfClock_destroy(anim->clock);
    free(anim);
}
