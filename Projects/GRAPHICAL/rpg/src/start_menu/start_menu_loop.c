/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** start_menu_loop
*/

#include "rpg_header.h"

static void set_position_start_menu(gamedata_t *gamedata)
{
    sfSprite_setPosition(gamedata->menu->startmenu->background->sprite,
    (sfVector2f){0, 0});
    sfSprite_setPosition(gamedata->menu->startmenu->first_panel->sprite,
    (sfVector2f){(1920 / 2) - 472, 450});
    sfSprite_setPosition(gamedata->menu->startmenu->settings->sprite->sprite,
    (sfVector2f){(1920 / 2) - 435, 488});
    sfSprite_setPosition(gamedata->menu->startmenu->play->sprite->sprite,
    (sfVector2f){(1920 / 2) - 211, 488});
    sfSprite_setPosition(gamedata->menu->startmenu->credits->sprite->sprite,
    (sfVector2f){(1920 / 2) + 11, 488});
    sfSprite_setPosition(gamedata->menu->startmenu->leave->sprite->sprite,
    (sfVector2f){(1920 / 2) + 233, 488});
}

static void draw_start_menu(gamedata_t *gamedata)
{
    if (sfMusic_getStatus(gamedata->music->menu) == sfStopped)
        sfMusic_play(gamedata->music->menu);
    sfRenderWindow_clear(gamedata->window->window, sfBlack);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->background->sprite, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->startmenu->titre->text, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->first_panel->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->settings->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->play->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->credits->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->leave->sprite->sprite, NULL);
    sfRenderWindow_display(gamedata->window->window);
}

void start_menu_loop(gamedata_t *gamedata, sfEvent *event)
{
    gamedata->entity->player->movement->direction = (sfVector2f){0, 0};
    update_position(gamedata);
    sfMusic_stop(gamedata->music->world);
    sfMusic_stop(gamedata->music->epic);
    sfView_setSize(gamedata->window->view, (sfVector2f){1920, 1080});
    sfView_setCenter(gamedata->window->view, (sfVector2f){960, 540});
    sfRenderWindow_setView(gamedata->window->window, gamedata->window->view);
    set_position_start_menu(gamedata);
    draw_start_menu(gamedata);
    while (sfRenderWindow_pollEvent(gamedata->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(gamedata->window->window);
        button_event(gamedata, event, gamedata->menu->startmenu->settings);
        button_event(gamedata, event, gamedata->menu->startmenu->play);
        button_event(gamedata, event, gamedata->menu->startmenu->credits);
        button_event(gamedata, event, gamedata->menu->startmenu->leave);
    }
}
