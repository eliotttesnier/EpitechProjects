/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** fill_menus
*/

#include "rpg_header.h"

static void set_position_settings(gamedata_t *game)
{
    sfSprite_setPosition(game->menu->startmenu->background->sprite,
        (sfVector2f){0, 0});
    sfSprite_setPosition(game->menu->optionmenu->back->sprite->sprite,
        (sfVector2f){25, 25});
    sfSprite_setPosition(game->menu->optionmenu->winmenu->sprite,
        (sfVector2f){(1920 / 2) + 12.5, 25});
    sfSprite_setPosition(game->menu->optionmenu->soundmenu->sprite,
        (sfVector2f){(1920 / 2) - 612.5, 25});
    sfSprite_setPosition(game->menu->optionmenu->mus->back->sprite,
        (sfVector2f){(1920 / 2) - 350, 85});
    sfSprite_setPosition(game->menu->optionmenu->mus->dot->sprite,
        (sfVector2f){(1920 / 2) - 357 + game->settings->vol_music * 3, 83});
    sfSprite_setPosition(game->menu->optionmenu->sfx->back->sprite,
        (sfVector2f){(1920 / 2) - 350, 150});
    sfSprite_setPosition(game->menu->optionmenu->sfx->dot->sprite,
        (sfVector2f){(1920 / 2) - 357 + game->settings->vol_sfx * 3, 148});
    sfSprite_setPosition(game->menu->optionmenu->keymenu->sprite,
        (sfVector2f){(1920 / 2) - 612.5, 250});
}

static void set_resolution_text(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->fullscreentext = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Fullscreen :",
        (sfVector2f){(1920 / 2) + 70, 75}, (sfVector2f){0.75, 0.75});
    gamedata->menu->optionmenu->resolution = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "1920x1080 or 960x540 :",
        (sfVector2f){(1920 / 2) + 250, 75}, (sfVector2f){0.75, 0.75});
}

static void set_keybind_two(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->attack->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Attack :",
        (sfVector2f){(1920 / 2) + 25, 425}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->fire_spell->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Fire spell :",
        (sfVector2f){(1920 / 2) + 25, 575}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->heal_spell->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Heal spell :",
        (sfVector2f){(1920 / 2) + 25, 725}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->stun_spell->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Stun spell :",
        (sfVector2f){(1920 / 2) + 25, 875}, (sfVector2f){1, 1});
    set_keybind_button_text(gamedata);
    fill_keybind_button(gamedata);
}

static void create_keybind(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->forward = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->backward = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->left = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->right = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->inventory = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->interact = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->attack = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->fire_spell = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->heal_spell = malloc(sizeof(key_bind_t));
    gamedata->menu->optionmenu->stun_spell = malloc(sizeof(key_bind_t));
}

static void set_keybind(gamedata_t *gamedata)
{
    create_keybind(gamedata);
    gamedata->menu->optionmenu->forward->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Forward :",
        (sfVector2f){(1920 / 2) - 575, 275}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->backward->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Backward :",
        (sfVector2f){(1920 / 2) - 575, 425}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->left->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Left :",
        (sfVector2f){(1920 / 2) - 575, 575}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->right->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Right :",
        (sfVector2f){(1920 / 2) - 575, 725}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->interact->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Interact :",
        (sfVector2f){(1920 / 2) - 575, 875}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->inventory->name = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Inventory :",
        (sfVector2f){(1920 / 2) + 25, 275}, (sfVector2f){1, 1});
    set_keybind_two(gamedata);
}

static void set_settings_text(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->mustext = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Music :",
        (sfVector2f){(1920 / 2) - 575, 70}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->sfxtext = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Sound :",
        (sfVector2f){(1920 / 2) - 575, 135}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->musdata = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "100",
        (sfVector2f){(1920 / 2) - 440, 70}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->sfxdata = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "100",
        (sfVector2f){(1920 / 2) - 440, 135}, (sfVector2f){1, 1});
    set_resolution_text(gamedata);
    set_keybind(gamedata);
}

static void fill_action_toggle_optionmenu(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->fullscreen->func = toggle_fullscreen;
    gamedata->menu->optionmenu->resolutionscreen->func = resolutionscreen;
}

static void set_toggle_settings(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->fullscreen = create_toggle(
        (sfVector2f){(1920 / 2) + 90, 125});
    gamedata->menu->optionmenu->resolutionscreen = create_big_toggle(
        (sfVector2f){(1920 / 2) + 300, 125});
    fill_action_toggle_optionmenu(gamedata);
}

void fill_optionmenu(gamedata_t *gamedata, config_t *config)
{
    (void)config;
    gamedata->menu->optionmenu = malloc(sizeof(optionmenu_t));
    gamedata->menu->optionmenu->back = create_button(
        "assets/buttons/back(102x102).png", (sfIntRect){0, 0, 102, 102});
    gamedata->menu->optionmenu->mus = create_slider(
        "assets/buttons/slider_bar(300x10).png", (sfIntRect){0, 0, 300, 10},
        "assets/buttons/slider_dot(14x14).png", (sfIntRect){0, 0, 14, 14});
    gamedata->menu->optionmenu->sfx = create_slider(
        "assets/buttons/slider_bar(300x10).png", (sfIntRect){0, 0, 300, 10},
        "assets/buttons/slider_dot(14x14).png", (sfIntRect){0, 0, 14, 14});
    gamedata->menu->optionmenu->keymenu = create_sprite(
        "assets/buttons/key_menu(1225x700).png", (sfIntRect){0, 0, 1225, 700});
    gamedata->menu->optionmenu->soundmenu = create_sprite(
        "assets/buttons/sound_menu(600x200).png", (sfIntRect){0, 0, 600, 200});
    gamedata->menu->optionmenu->winmenu = create_sprite(
        "assets/buttons/sound_menu(600x200).png", (sfIntRect){0, 0, 600, 200});
    gamedata->menu->optionmenu->back->func = back_button;
    set_toggle_settings(gamedata);
    set_settings_text(gamedata);
    set_position_settings(gamedata);
}
