/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** swap_with_hang
*/

#include "rpg_header.h"

static void toggle_hover(gamedata_t *gamedata, toggle_t *toggle)
{
    sfVector2f mousePos = get_pixcoord(gamedata);

    if (is_on_sprite(toggle->toggle, mousePos) && toggle->active == false) {
        toggle->state = OFF_HOVERED;
    } else if (toggle->active == false) {
        toggle->state = OFF;
    }
    if (is_on_sprite(toggle->toggle, mousePos) && toggle->active == true) {
        toggle->state = ON_HOVERED;
    } else if (toggle->active == true) {
        toggle->state = ON;
    }
}

static void toggle_press(gamedata_t *gamedata, toggle_t *toggle)
{
    sfVector2f mousePos = get_pixcoord(gamedata);

    if (is_on_sprite(toggle->toggle, mousePos) && toggle->active == false) {
        toggle->state = ON;
    } else if (toggle->active == false) {
        toggle->state = OFF;
    }
    if (is_on_sprite(toggle->toggle, mousePos) && toggle->active == true) {
        toggle->state = OFF;
    } else if (toggle->active == true) {
        toggle->state = ON;
    }
}

static void draw_toggle_off(gamedata_t *gamedata, toggle_t *toggle)
{
    sfIntRect newPos;

    if (toggle->active == false) {
        if (toggle->state == OFF)
            newPos = (sfIntRect){toggle->toggle->rect.width * 2, 0,
                toggle->toggle->rect.width, toggle->toggle->rect.height};
        if (toggle->state == OFF_HOVERED)
            newPos = (sfIntRect){toggle->toggle->rect.width * 3, 0,
                toggle->toggle->rect.width, toggle->toggle->rect.height};
        if (toggle->state == ON) {
            newPos = (sfIntRect){0, 0,
                toggle->toggle->rect.width, toggle->toggle->rect.height};
            toggle->active = true;
            toggle->func((void *)gamedata);
        }
        sfSprite_setTextureRect(toggle->toggle->sprite, newPos);
        sfRenderWindow_drawSprite(gamedata->window->window,
            toggle->toggle->sprite, NULL);
    }
}

static void draw_toggle(gamedata_t *gamedata, toggle_t *toggle)
{
    sfIntRect newPos;

    if (toggle->active == true) {
        if (toggle->state == ON)
            newPos = (sfIntRect){0, 0, toggle->toggle->rect.width,
                toggle->toggle->rect.height};
        if (toggle->state == ON_HOVERED)
            newPos = (sfIntRect){toggle->toggle->rect.width, 0,
                toggle->toggle->rect.width, toggle->toggle->rect.height};
        if (toggle->state == OFF) {
            newPos = (sfIntRect){toggle->toggle->rect.width * 2, 0,
                toggle->toggle->rect.width, toggle->toggle->rect.height};
            toggle->active = false;
            toggle->func((void *)gamedata);
        }
        sfSprite_setTextureRect(toggle->toggle->sprite, newPos);
        sfRenderWindow_drawSprite(gamedata->window->window,
            toggle->toggle->sprite, NULL);
    }
}

void toggle_event(gamedata_t *gamedata, sfEvent *event, toggle_t *toggle)
{
    toggle_hover(gamedata, toggle);
    if (event->type == sfEvtMouseButtonPressed)
        toggle_press(gamedata, toggle);
    draw_toggle(gamedata, toggle);
    draw_toggle_off(gamedata, toggle);
}
