/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** dragndrop
*/

#include "rpg_header.h"

static void set_position_ingame_menu(gamedata_t *gamedata, sfVector2f center)
{
    sfSprite_setPosition(gamedata->menu->gamemenu->close->sprite->sprite,
    (sfVector2f){center.x - 225, center.y - 125});
    sfSprite_setPosition(gamedata->menu->gamemenu->panel->sprite,
    (sfVector2f){center.x - 87.75, center.y - 20});
    sfSprite_setPosition(gamedata->menu->gamemenu->inventory->sprite->sprite,
    (sfVector2f){center.x - 80, center.y - 10});
    sfSprite_setPosition(gamedata->menu->gamemenu->save->sprite->sprite,
    (sfVector2f){center.x - 45, center.y - 10});
    sfSprite_setPosition(gamedata->menu->gamemenu->load->sprite->sprite,
    (sfVector2f){center.x - 10, center.y - 10});
    sfSprite_setPosition(gamedata->menu->gamemenu->option->sprite->sprite,
    (sfVector2f){center.x + 25, center.y - 10});
    sfSprite_setPosition(gamedata->menu->gamemenu->quit->sprite->sprite,
    (sfVector2f){center.x + 60, center.y - 10});
}

static void draw_ingame_menu(gamedata_t *gamedata)
{
    game_display(gamedata, true);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->gamemenu->panel->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->gamemenu->inventory->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->gamemenu->load->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->gamemenu->option->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->gamemenu->quit->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->gamemenu->save->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->gamemenu->close->sprite->sprite, NULL);
    sfRenderWindow_display(gamedata->window->window);
}

void ingame_menu_loop(gamedata_t *gamedata, sfEvent *event)
{
    sfVector2f center = sfView_getCenter(gamedata->window->view);

    gamedata->entity->player->movement->direction = (sfVector2f){0, 0};
    update_position(gamedata);
    set_position_ingame_menu(gamedata, center);
    draw_ingame_menu(gamedata);
    while (sfRenderWindow_pollEvent(gamedata->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(gamedata->window->window);
        if (event->type == sfEvtKeyPressed && (event->key.code == sfKeyEscape
            || event->key.code == gamedata->settings->keys[INVENTORY]))
            gamedata->menu->gamemenu->close->func((void *)gamedata);
        button_event(gamedata, event, gamedata->menu->gamemenu->inventory);
        button_event(gamedata, event, gamedata->menu->gamemenu->load);
        button_event(gamedata, event, gamedata->menu->gamemenu->option);
        button_event(gamedata, event, gamedata->menu->gamemenu->quit);
        button_event(gamedata, event, gamedata->menu->gamemenu->save);
        button_event(gamedata, event, gamedata->menu->gamemenu->close);
    }
}
