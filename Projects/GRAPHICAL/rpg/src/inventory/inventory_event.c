/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** inventory_event
*/

#include "rpg_header.h"

void inventory_key_pressed(gamedata_t *game, sfEvent *event)
{
    if (event->key.code == game->settings->keys[INVENTORY] ||
        event->key.code == sfKeyEscape) {
        if (game->inventory->hanging != NULL)
            remove_from_hang(game);
        game->scene = game->prescene;
        game->prescene = S_INVENTORY;
    }
}

void inventory_click(gamedata_t *game, sfVector2f pix)
{
    if (game->inventory->hanging == NULL)
        inventory_drag(game, pix);
}

void inventory_released(gamedata_t *game, sfVector2f pix)
{
    if (game->inventory->hanging == NULL)
        return;
    inventory_drop(game, pix);
}

void inventory_event(gamedata_t *game, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(game->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(game->window->window);
        if (event->type == sfEvtKeyPressed)
            inventory_key_pressed(game, event);
        if (event->type == sfEvtMouseButtonPressed &&
            event->mouseButton.button == sfMouseLeft)
            inventory_click(game, get_pixcoord(game));
        if (event->type == sfEvtMouseButtonReleased &&
            event->mouseButton.button == sfMouseLeft)
            inventory_released(game, get_pixcoord(game));
        if (event->type == sfEvtMouseButtonPressed &&
            event->mouseButton.button == sfMouseRight)
            inventory_consume(game, get_pixcoord(game));
    }
}
