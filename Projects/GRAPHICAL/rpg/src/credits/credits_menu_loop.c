/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** credits menu loop
*/

#include "rpg_header.h"

void move_back(gamedata_t *game)
{
    credit_menu_t *menu = game->menu->creditmenu;
    float time = sfClock_getElapsedTime(menu->clock).microseconds;

    if (time > (sfKeyboard_isKeyPressed(sfKeySpace) ? 7500 : 7500 * 5 / 2)) {
        sfClock_restart(menu->clock);
        sfSprite_move(menu->display->sprite, (sfVector2f){0, -1});
    }
}

void credit_button_state(gamedata_t *game)
{
    button_t *but = game->menu->creditmenu->backbutt;
    sfVector2f pix = get_pixcoord(game);

    if (but->state != PRESS)
        but->state = RELEASE;
    if (but->state != PRESS && is_on_button(but, pix))
        but->state = HOVERED;
    but->sprite->rect.left = but->state * but->sprite->rect.width;
    sfSprite_setTextureRect(but->sprite->sprite, but->sprite->rect);
}

void credits_menu_loop(gamedata_t *game, sfEvent *event)
{
    if (sfMusic_getStatus(game->music->epic) == sfStopped)
        sfMusic_play(game->music->epic);
    sfMusic_stop(game->music->menu);
    credits_event(game, event);
    if (sfSprite_getGlobalBounds(game->menu->creditmenu->display->sprite).top
        <= - 7560) {
        game->scene = S_START_MENU;
        sfSprite_setPosition(game->menu->creditmenu->display->sprite,
            (sfVector2f){0, 1080});
        }
    credit_button_state(game);
    move_back(game);
    credits_display(game);
}
