/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** Game loading loop
*/

#include "rpg_header.h"

static void draw_game_loading(gamedata_t *gamedata)
{
    sfRenderWindow_clear(gamedata->window->window, sfBlack);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->background->sprite, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->startmenu->titre->text, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->second_panel->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->newsave->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->load->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->back->sprite->sprite, NULL);
    if (!is_there_save())
        sfRenderWindow_drawSprite(gamedata->window->window,
            gamedata->menu->startmenu->grayed->sprite, NULL);
    sfRenderWindow_display(gamedata->window->window);
}

static void set_position_game_loading(gamedata_t *gamedata)
{
    sfSprite_setPosition(gamedata->menu->startmenu->background->sprite,
        (sfVector2f){0, 0});
    sfSprite_setPosition(gamedata->menu->startmenu->second_panel->sprite,
        (sfVector2f){(1920 / 2) - 242, 450});
    sfSprite_setPosition(gamedata->menu->startmenu->newsave->sprite->sprite,
        (sfVector2f){(1920 / 2) - 207, 488});
    sfSprite_setPosition(gamedata->menu->startmenu->load->sprite->sprite,
        (sfVector2f){(1920 / 2) + 5, 488});
    sfSprite_setPosition(gamedata->menu->startmenu->grayed->sprite,
        (sfVector2f){(1920 / 2) + 5, 488});
    sfSprite_setPosition(gamedata->menu->startmenu->back->sprite->sprite,
        (sfVector2f){25, 25});
}

void game_loading_loop(gamedata_t *gamedata, sfEvent *event)
{
    set_position_game_loading(gamedata);
    draw_game_loading(gamedata);
    while (sfRenderWindow_pollEvent(gamedata->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(gamedata->window->window);
        button_event(gamedata, event, gamedata->menu->startmenu->newsave);
        if (is_there_save())
            button_event(gamedata, event, gamedata->menu->startmenu->load);
        button_event(gamedata, event, gamedata->menu->startmenu->back);
    }
}
