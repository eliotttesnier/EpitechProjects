/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** create_sprite
*/

#include "rpg_header.h"

button_t *create_button(char *path, sfIntRect rect)
{
    button_t *new = malloc(sizeof(button_t));

    new->sprite = create_sprite(path, rect);
    new->clickable = true;
    new->state = RELEASE;
    new->func = NULL;
    return (new);
}

sprite_t *create_sprite(char *path, sfIntRect rect)
{
    sprite_t *new = malloc(sizeof(sprite_t) * 1);

    new->rect = rect;
    new->texture = sfTexture_createFromFile(path, NULL);
    if (new->texture == NULL)
        exit(84);
    new->sprite = sfSprite_create();
    sfSprite_setTexture(new->sprite, new->texture, sfTrue);
    sfSprite_setTextureRect(new->sprite, new->rect);
    return (new);
}

sfTexture *create_texture(char *path)
{
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    if (texture == NULL)
        exit(84);
    return (texture);
}
