/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** buttons actions
*/

#include "rpg_header.h"

void button_hover(gamedata_t *gamedata, button_t *button)
{
    sfVector2f mousePos = get_pixcoord(gamedata);

    if (is_on_button(button, mousePos)) {
        button->state = HOVERED;
    } else {
        button->state = RELEASE;
    }
}

void button_press(gamedata_t *gamedata, button_t *button)
{
    sfVector2f mousePos = get_pixcoord(gamedata);

    if (is_on_button(button, mousePos)) {
        button->state = PRESS;
    } else {
        button->state = RELEASE;
    }
}

void draw_button(gamedata_t *gamedata, button_t *button)
{
    sfIntRect newPos;

    if (button->state == RELEASE)
        newPos = (sfIntRect){0, 0, button->sprite->rect.width,
            button->sprite->rect.height};
    if (button->state == HOVERED)
        newPos = (sfIntRect){button->sprite->rect.width, 0,
            button->sprite->rect.width, button->sprite->rect.height};
    if (button->state == PRESS) {
        newPos = (sfIntRect){button->sprite->rect.width * 2, 0,
            button->sprite->rect.width, button->sprite->rect.height};
    }
    sfSprite_setTextureRect(button->sprite->sprite, newPos);
    sfRenderWindow_drawSprite(gamedata->window->window, button->sprite->sprite,
        NULL);
}

void button_event(gamedata_t *gamedata, sfEvent *event, button_t *buton)
{
    button_hover(gamedata, buton);
    if (event->type == sfEvtMouseButtonPressed)
        button_press(gamedata, buton);
    draw_button(gamedata, buton);
    if (event->type == sfEvtMouseButtonReleased &&
        is_on_button(buton, get_pixcoord(gamedata)))
        buton->func((void *)gamedata);
}
