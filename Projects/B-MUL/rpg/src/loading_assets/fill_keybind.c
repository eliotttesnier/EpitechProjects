/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** ventory
*/

#include "rpg_header.h"

static void set_keybind_button_text_two(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->attack->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Space",
        (sfVector2f){(1920 / 2) + 475, 435}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->fire_spell->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "G",
        (sfVector2f){(1920 / 2) + 475, 585}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->heal_spell->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "H",
        (sfVector2f){(1920 / 2) + 475, 735}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->stun_spell->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "J",
        (sfVector2f){(1920 / 2) + 475, 885}, (sfVector2f){1, 1});
    set_pos_keybind_button(gamedata->menu->optionmenu);
}

void set_keybind_button_text(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->forward->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Z",
        (sfVector2f){(1920 / 2) - 175, 300}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->backward->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "S",
        (sfVector2f){(1920 / 2) - 175, 435}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->left->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "Q",
        (sfVector2f){(1920 / 2) - 175, 585}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->right->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "D",
        (sfVector2f){(1920 / 2) - 175, 735}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->interact->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "F",
        (sfVector2f){(1920 / 2) - 175, 885}, (sfVector2f){1, 1});
    gamedata->menu->optionmenu->inventory->key = create_text_menu(
        "assets/fonts/AdventureRequest-j8W9.ttf", "E",
        (sfVector2f){(1920 / 2) + 475, 300}, (sfVector2f){1, 1});
    set_keybind_button_text_two(gamedata);
}

static void set_keybind_function(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->forward->button->func = forward_key;
    gamedata->menu->optionmenu->backward->button->func = backward_key;
    gamedata->menu->optionmenu->left->button->func = left_key;
    gamedata->menu->optionmenu->right->button->func = right_key;
    gamedata->menu->optionmenu->inventory->button->func = inventory_key;
    gamedata->menu->optionmenu->interact->button->func = interact_key;
    gamedata->menu->optionmenu->attack->button->func = attack_key;
    gamedata->menu->optionmenu->fire_spell->button->func = fire_spell_key;
    gamedata->menu->optionmenu->heal_spell->button->func = heal_spell_key;
    gamedata->menu->optionmenu->stun_spell->button->func = stun_spell_key;
}

static void set_keybind_position_two(gamedata_t *gamedata)
{
    sfSprite_setPosition(
        gamedata->menu->optionmenu->inventory->button->sprite->sprite,
        (sfVector2f){(1920 / 2) + 375, 275});
    sfSprite_setPosition(
        gamedata->menu->optionmenu->attack->button->sprite->sprite,
        (sfVector2f){(1920 / 2) + 375, 405});
    sfSprite_setPosition(
        gamedata->menu->optionmenu->fire_spell->button->sprite->sprite,
        (sfVector2f){(1920 / 2) + 375, 555});
    sfSprite_setPosition(
        gamedata->menu->optionmenu->heal_spell->button->sprite->sprite,
        (sfVector2f){(1920 / 2) + 375, 705});
    sfSprite_setPosition(
        gamedata->menu->optionmenu->stun_spell->button->sprite->sprite,
        (sfVector2f){(1920 / 2) + 375, 855});
}

static void set_keybind_position(gamedata_t *gamedata)
{
    sfSprite_setPosition(
        gamedata->menu->optionmenu->forward->button->sprite->sprite,
        (sfVector2f){(1920 / 2) - 275, 275});
    sfSprite_setPosition(
        gamedata->menu->optionmenu->backward->button->sprite->sprite,
        (sfVector2f){(1920 / 2) - 275, 405});
    sfSprite_setPosition(
        gamedata->menu->optionmenu->left->button->sprite->sprite,
        (sfVector2f){(1920 / 2) - 275, 555});
    sfSprite_setPosition(
        gamedata->menu->optionmenu->right->button->sprite->sprite,
        (sfVector2f){(1920 / 2) - 275, 705});
    sfSprite_setPosition(
        gamedata->menu->optionmenu->interact->button->sprite->sprite,
        (sfVector2f){(1920 / 2) - 275, 855});
    set_keybind_position_two(gamedata);
}

static void set_keybind_button_two(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->stun_spell->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    set_keybind_function(gamedata);
    set_keybind_position(gamedata);
}

void fill_keybind_button(gamedata_t *gamedata)
{
    gamedata->menu->optionmenu->forward->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->optionmenu->backward->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->optionmenu->left->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->optionmenu->right->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->optionmenu->interact->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->optionmenu->inventory->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->optionmenu->attack->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->optionmenu->fire_spell->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->optionmenu->heal_spell->button = create_button(
        "assets/buttons/key_bind(202x77).png", (sfIntRect){0, 0, 202, 77});
    set_keybind_button_two(gamedata);
}
