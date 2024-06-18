/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** settings menu buttons function
*/

#include "rpg_header.h"

void set_icon_framerate(gamedata_t *game)
{
    sfRenderWindow_setIcon(game->window->window, 100, 100, game->window->icon);
    sfRenderWindow_setFramerateLimit(game->window->window, FRAMERATE);
}

void slider_action(gamedata_t *gamedata, slider_t *slider)
{
    sfVector2f mousePos = get_pixcoord(gamedata);
    sfVector2f dotPos = sfSprite_getPosition(slider->dot->sprite);
    sfVector2f backpos = sfSprite_getPosition(slider->back->sprite);

    if (slider->clicked == false)
        return;
    if (mousePos.x < sfSprite_getPosition(slider->back->sprite).x - 7) {
        sfSprite_setPosition(slider->dot->sprite,
            (sfVector2f){backpos.x - 7, dotPos.y});
        return;
    }
    if (mousePos.x > sfSprite_getPosition(slider->back->sprite).x + 293.0) {
        sfSprite_setPosition(slider->dot->sprite,
            (sfVector2f){backpos.x + 293.0, dotPos.y});
        return;
    }
    sfSprite_setPosition(slider->dot->sprite,
        (sfVector2f){mousePos.x, dotPos.y});
}

static void recover_fullscreen(gamedata_t *game)
{
    game->menu->optionmenu->fullscreen->state = OFF;
    game->menu->optionmenu->fullscreen->active = false;
    sfSprite_setTextureRect(game->menu->optionmenu->fullscreen->toggle->sprite,
        (sfIntRect){game->menu->optionmenu->fullscreen->toggle->rect.width * 2,
        0, game->menu->optionmenu->fullscreen->toggle->rect.width,
        game->menu->optionmenu->fullscreen->toggle->rect.height});
    game->window->fullscreen = false;
}

static void little_screen(gamedata_t *game)
{
    sfRenderWindow_close(game->window->window);
    game->window->resolution = (sfVideoMode){960, 540, 32};
    game->window->window = sfRenderWindow_create(game->window->resolution,
    "The Legend of Damopies", sfResize | sfClose, NULL);
    set_icon_framerate(game);
}

void resolutionscreen(void *gamedata)
{
    gamedata_t *game = (gamedata_t *)gamedata;

    recover_fullscreen(game);
    if (game->window->fullscreen) {
        sfRenderWindow_close(game->window->window);
        game->window->resolution = (sfVideoMode){1920, 1080, 32};
        game->window->window = sfRenderWindow_create(game->window->resolution,
        "The Legend of Damopies", sfResize | sfClose, NULL);
        set_icon_framerate(game);
    } else if (game->menu->optionmenu->resolutionscreen->active == true){
        sfRenderWindow_close(game->window->window);
        game->window->resolution = (sfVideoMode){1920, 1080, 32};
        game->window->window = sfRenderWindow_create(game->window->resolution,
        "The Legend of Damopies", sfResize | sfClose, NULL);
        set_icon_framerate(game);
    } else {
        little_screen(game);
    }
}
