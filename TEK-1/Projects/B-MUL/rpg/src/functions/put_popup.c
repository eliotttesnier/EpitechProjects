/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** put_popup
*/

#include "rpg_header.h"

void put_popup(gamedata_t *game, char *msg)
{
    sfFloatRect rect;

    if (game->hud->popup->msg != NULL) {
        free(game->hud->popup->msg);
        game->hud->popup->msg = NULL;
    }
    sfClock_restart(game->hud->popup->time_since_display);
    game->hud->popup->msg = create_text("assets/fonts/main_font.ttf");
    game->hud->popup->msg->str = strdup(msg);
    sfText_setString(game->hud->popup->msg->text, game->hud->popup->msg->str);
    sfText_setOutlineColor(game->hud->popup->msg->text, sfBlack);
    sfText_setOutlineThickness(game->hud->popup->msg->text, 1.00);
    rect = sfText_getGlobalBounds(game->hud->popup->msg->text);
    sfText_setOrigin(game->hud->popup->msg->text,
        (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setScale(game->hud->popup->msg->text, (sfVector2f){0.35, 0.35});
}
