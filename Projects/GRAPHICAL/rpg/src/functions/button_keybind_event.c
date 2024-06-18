/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** buttons actions
*/

#include "rpg_header.h"

static void button_keybind_hover(gamedata_t *gamedata, button_t *button)
{
    sfVector2f mousePos = get_pixcoord(gamedata);

    if (is_on_button(button, mousePos)) {
        button->state = HOVERED;
    } else {
        button->state = RELEASE;
    }
}

static void button_keybind_press(gamedata_t *gamedata, button_t *button)
{
    sfVector2f mousePos = get_pixcoord(gamedata);

    if (is_on_button(button, mousePos)) {
        button->state = PRESS;
    } else {
        button->state = RELEASE;
    }
}

static void draw_keybind_button(gamedata_t *gamedata, button_t *button)
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

static void button_keybind_event(gamedata_t *gamedata, sfEvent *event,
    key_bind_t *key)
{
    button_keybind_hover(gamedata, key->button);
    if (event->type == sfEvtMouseButtonPressed)
        button_keybind_press(gamedata, key->button);
    draw_keybind_button(gamedata, key->button);
    if (event->type == sfEvtMouseButtonReleased &&
        is_on_button(key->button, get_pixcoord(gamedata)))
        key->button->func((void *)gamedata);
}

void button_event_keybind(gamedata_t *gamedata, sfEvent *event)
{
    button_keybind_event(gamedata, event, gamedata->menu->optionmenu->forward);
    button_keybind_event(gamedata, event,
        gamedata->menu->optionmenu->backward);
    button_keybind_event(gamedata, event, gamedata->menu->optionmenu->left);
    button_keybind_event(gamedata, event, gamedata->menu->optionmenu->right);
    button_keybind_event(gamedata, event,
        gamedata->menu->optionmenu->interact);
    button_keybind_event(gamedata, event,
        gamedata->menu->optionmenu->inventory);
    button_keybind_event(gamedata, event, gamedata->menu->optionmenu->attack);
    button_keybind_event(gamedata, event,
        gamedata->menu->optionmenu->fire_spell);
    button_keybind_event(gamedata, event,
        gamedata->menu->optionmenu->heal_spell);
    button_keybind_event(gamedata, event,
        gamedata->menu->optionmenu->stun_spell);
}
