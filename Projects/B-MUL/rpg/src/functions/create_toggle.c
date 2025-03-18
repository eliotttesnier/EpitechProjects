/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** add_to_inv
*/

#include "rpg_header.h"

toggle_t *create_toggle(sfVector2f pos)
{
    toggle_t *new = malloc(sizeof(toggle_t));

    new->active = false;
    new->state = OFF;
    new->toggle = create_sprite("assets/buttons/fullscreen_toggle(400x50).png",
        (sfIntRect){200, 0, 100, 50});
    sfSprite_setPosition(new->toggle->sprite, pos);
    return new;
}

big_toggle_t *create_big_toggle(sfVector2f pos)
{
    big_toggle_t *new = malloc(sizeof(big_toggle_t));

    new->active = true;
    new->state = ON;
    new->toggle = create_sprite("assets/buttons/resolution_toggle(800x50).png",
        (sfIntRect){0, 0, 200, 50});
    sfSprite_setPosition(new->toggle->sprite, pos);
    return new;
}
