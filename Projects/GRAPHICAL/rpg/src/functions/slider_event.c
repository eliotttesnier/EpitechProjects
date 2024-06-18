/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** slider event
*/

#include "rpg_header.h"


static void slider_use(gamedata_t *gamedata, slider_t *slider)
{
    sfVector2f mousePos = get_pixcoord(gamedata);

    if (is_on_sprite(slider->dot, mousePos)) {
        slider->clicked = true;
    }
}

void slider_event(gamedata_t *gamedata, sfEvent *event, slider_t *slider)
{
    if (event->type == sfEvtMouseButtonPressed)
        slider_use(gamedata, slider);
    if (event->type == sfEvtMouseButtonReleased)
        slider->clicked = false;
}
