/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** settings menu loop
*/

#include "rpg_header.h"

void set_sfx_sound(gamedata_t *game)
{
    float vol = game->settings->vol_sfx;

    for (int i = 0; i < NB_SFX; i++) {
        sfMusic_setVolume(game->sfx->sounds[i], vol);
    }
}

static void slider_update(gamedata_t *gamedata)
{
    gamedata->settings->vol_music = 100 - ((580 -
        sfSprite_getPosition(gamedata->menu->optionmenu->mus->dot->sprite).x)
        * 100 / 300) - 107;
    gamedata->settings->vol_sfx = 100 - ((580 -
        sfSprite_getPosition(gamedata->menu->optionmenu->sfx->dot->sprite).x)
        * 100 / 300) - 107;
    sfMusic_setVolume(gamedata->music->menu,
        gamedata->settings->vol_music);
    sfMusic_setVolume(gamedata->music->epic,
        gamedata->settings->vol_music);
    sfMusic_setVolume(gamedata->music->world,
        gamedata->settings->vol_music);
    set_sfx_sound(gamedata);
    sfText_setString(gamedata->menu->optionmenu->musdata->text,
        my_itoa(gamedata->settings->vol_music));
    sfText_setString(gamedata->menu->optionmenu->sfxdata->text,
        my_itoa(gamedata->settings->vol_sfx));
}

static void draw_settings_text(gamedata_t *gamedata)
{
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->sfxtext->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->mustext->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->musdata->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->sfxdata->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->fullscreentext->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->resolution->text, NULL);
}

static void draw_settings_button(gamedata_t *gamedata)
{
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->startmenu->background->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->back->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->keymenu->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->soundmenu->sprite, NULL);
        sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->winmenu->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->mus->back->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->mus->dot->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->sfx->back->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->sfx->dot->sprite, NULL);
}

static void draw_settings_toggle(gamedata_t *gamedata)
{
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->fullscreen->toggle->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->resolutionscreen->toggle->sprite, NULL);
}

static void draw_keybind_title(gamedata_t *gamedata)
{
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->forward->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->backward->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->left->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->right->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->interact->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->inventory->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->attack->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->fire_spell->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->heal_spell->name->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->stun_spell->name->text, NULL);
}

static void draw_key_bind(gamedata_t *gamedata)
{
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->forward->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->backward->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->left->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->right->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->interact->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->inventory->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->attack->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->fire_spell->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->heal_spell->key->text, NULL);
    sfRenderWindow_drawText(gamedata->window->window,
        gamedata->menu->optionmenu->stun_spell->key->text, NULL);
}

static void draw_game_loading(gamedata_t *gamedata)
{
    sfRenderWindow_clear(gamedata->window->window, sfBlack);
    draw_settings_button(gamedata);
    draw_key_bind_button(gamedata);
    draw_settings_toggle(gamedata);
    draw_settings_text(gamedata);
    draw_keybind_title(gamedata);
    draw_key_bind(gamedata);
    sfRenderWindow_display(gamedata->window->window);
}

void settings_menu_loop(gamedata_t *gamedata, sfEvent *event)
{
    gamedata->entity->player->movement->direction = (sfVector2f){0, 0};
    update_position(gamedata);
    sfView_setSize(gamedata->window->view, (sfVector2f){1920, 1080});
    sfView_setCenter(gamedata->window->view, (sfVector2f){960, 540});
    sfRenderWindow_setView(gamedata->window->window, gamedata->window->view);
    draw_game_loading(gamedata);
    while (sfRenderWindow_pollEvent(gamedata->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(gamedata->window->window);
        button_event(gamedata, event, gamedata->menu->optionmenu->back);
        slider_event(gamedata, event, gamedata->menu->optionmenu->mus);
        slider_action(gamedata, gamedata->menu->optionmenu->mus);
        slider_event(gamedata, event, gamedata->menu->optionmenu->sfx);
        slider_action(gamedata, gamedata->menu->optionmenu->sfx);
        slider_update(gamedata);
        toggle_event(gamedata, event, gamedata->menu->optionmenu->fullscreen);
        big_toggle_event(gamedata, event,
            gamedata->menu->optionmenu->resolutionscreen);
        button_event_keybind(gamedata, event);
    }
}
