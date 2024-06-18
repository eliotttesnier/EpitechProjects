/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_objects
*/

#include "rpg_header.h"

void free_chest(chest_t *chest)
{
    if (chest == NULL)
        return;
    free_chest(chest->next);
    free_animation(chest->animation);
    free_sprite(chest->sprite);
    free(chest->path);
    free(chest);
}

void free_obj(object_t *obj)
{
    free_chest(obj->chests);
    free_sprite(obj->bridge->broken);
    free_sprite(obj->bridge->fixed);
    free(obj->bridge);
    free(obj);
}
