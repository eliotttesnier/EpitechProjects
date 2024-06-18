/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** display_hud
*/

#include "rpg_header.h"

static sfVector2f get_map_pos(gamedata_t *game, sfVector2f center)
{
    sfVector2f p = game->entity->player->position;
    sfVector2f pos = (sfVector2f){(p.x / 6400) * 100, (p.y / 6432) * 100};

    pos.x += center.x + 135 - 0.5;
    pos.y += center.y - 130 - 0.5;
    (void)p;
    return (pos);
}

void hud_position(gamedata_t *game)
{
    sfVector2f center = sfView_getCenter(game->window->view);

    sfSprite_setPosition(game->hud->minimap->map->sprite,
        (sfVector2f){center.x + 135, center.y - 130});
    sfSprite_setPosition(game->hud->minimap->player->sprite,
        get_map_pos(game, center));
    sfSprite_setPosition(game->hud->minimap->cadre->sprite,
        (sfVector2f){center.x + 134, center.y - 131});
    if (game->hud->popup->msg != NULL) {
        sfText_setPosition(game->hud->popup->msg->text,
            (sfVector2f){center.x, center.y + 90});
        sfSprite_setPosition(game->hud->popup->back->sprite,
            (sfVector2f){center.x, center.y + 100});
    }
}

static void display_map(gamedata_t *game)
{
    sfRenderWindow_drawSprite(game->window->window,
        game->hud->minimap->map->sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->hud->minimap->player->sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->hud->minimap->cadre->sprite, NULL);
}

static void display_popup(gamedata_t *game)
{
    if (game->hud->popup->msg == NULL)
        return;
    sfRenderWindow_drawSprite(game->window->window,
        game->hud->popup->back->sprite, NULL);
    sfRenderWindow_drawText(game->window->window,
        game->hud->popup->msg->text, NULL);
}

static void display_text_hud(gamedata_t *game)
{
    sfVector2f center = sfView_getCenter(game->window->view);

    sfText_scale(game->hud->hp->text, (sfVector2f){0.5, 0.5});
    sfText_scale(game->hud->mana->text, (sfVector2f){0.5, 0.5});
    sfText_scale(game->hud->xp->text, (sfVector2f){0.5, 0.5});
    sfText_setPosition(game->hud->hp->text,
        (sfVector2f){center.x - 235, center.y - 135});
    sfText_setPosition(game->hud->mana->text,
        (sfVector2f){center.x - 235, center.y - 115});
    sfText_setPosition(game->hud->xp->text,
        (sfVector2f){center.x - 235, center.y - 95});
    sfText_setColor(game->hud->hp->text, sfGreen);
    sfRenderWindow_drawText(game->window->window, game->hud->hp->text, NULL);
    sfText_setColor(game->hud->mana->text, sfBlue);
    sfRenderWindow_drawText(game->window->window, game->hud->mana->text, NULL);
    sfRenderWindow_drawText(game->window->window, game->hud->xp->text, NULL);
}

void display_adv(gamedata_t *game)
{
    sfVector2f center = sfView_getCenter(game->window->view);

    sfSprite_setPosition(game->hud->adv[game->adv]->sprite,
        (sfVector2f){center.x - 1920 / 8, center.y - 1080 / 8});
    sfRenderWindow_drawSprite(game->window->window,
        game->hud->adv[game->adv]->sprite, NULL);
}

void display_hud(gamedata_t *game)
{
    hud_position(game);
    display_map(game);
    display_popup(game);
    display_text_hud(game);
    display_adv(game);
}
