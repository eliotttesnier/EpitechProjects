/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** create_button
*/

#include "include/my_paint_header.h"

static void fill_static_sprite(s_button *button, char *path)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    sfSprite_setTexture(sprite, texture, sfFalse);
    button->sprites[0] = sprite;
    button->textures[0] = texture;
}

static void fill_hover_sprite(s_button *button, char *path)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    sfSprite_setTexture(sprite, texture, sfFalse);
    button->sprites[1] = sprite;
    button->textures[1] = texture;
}

static void fill_clicked_sprite(s_button *button, char *path)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    sfSprite_setTexture(sprite, texture, sfFalse);
    button->sprites[2] = sprite;
    button->textures[2] = texture;
}

s_button *create_button(char *asset, void (*func)(void))
{
    s_button *button = malloc(sizeof(s_button));

    button->sprites = malloc(sizeof(sfSprite *) * 3);
    button->textures = malloc(sizeof(sfTexture *) * 3);
    fill_static_sprite(button, my_strcat("./assets/static/", asset));
    fill_hover_sprite(button, my_strcat("./assets/hover/", asset));
    fill_clicked_sprite(button, my_strcat("./assets/clicked/", asset));
    button->state = STATIC;
    button->action = func;
    return (button);
}
