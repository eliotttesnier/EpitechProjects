/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** credits_event
*/

#include "rpg_header.h"

void credit_mouse_released(gamedata_t *game)
{
    button_t *but = game->menu->creditmenu->backbutt;
    sfVector2f pix = get_pixcoord(game);

    if (is_on_button(but, pix)) {
        but->state = RELEASE;
        game->scene = S_START_MENU;
        game->prescene = S_CREDITS_MENU;
        sfSprite_setPosition(game->menu->creditmenu->display->sprite,
            (sfVector2f){0, 1080});
    }
    but->state = RELEASE;
}

void credit_mouse_pressed(gamedata_t *game)
{
    button_t *but = game->menu->creditmenu->backbutt;
    sfVector2f pix = get_pixcoord(game);

    if (is_on_button(but, pix))
        but->state = PRESS;
}

void credits_event(gamedata_t *game, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(game->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(game->window->window);
        if (event->type == sfEvtMouseButtonReleased)
            credit_mouse_released(game);
        if (event->type == sfEvtMouseButtonPressed)
            credit_mouse_pressed(game);
    }
}
