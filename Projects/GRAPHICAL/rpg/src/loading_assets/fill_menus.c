/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** fill_menus
*/

#include "rpg_header.h"

static void set_title(gamedata_t *gamedata)
{
    sfColor color = sfColor_fromRGB(202, 170, 103);

    gamedata->menu->startmenu->titre = create_text(
        "assets/fonts/main_font.ttf");
    gamedata->menu->startmenu->titre->str = strdup("The Legend of Damopies");
    sfText_setString(gamedata->menu->startmenu->titre->text,
        gamedata->menu->startmenu->titre->str);
    sfText_setPosition(gamedata->menu->startmenu->titre->text,
        (sfVector2f){360, 200});
    sfText_scale(gamedata->menu->startmenu->titre->text, (sfVector2f){2, 2});
    sfText_setCharacterSize(gamedata->menu->startmenu->titre->text, 75);
    sfText_setColor(gamedata->menu->startmenu->titre->text, color);
    sfText_setOutlineColor(gamedata->menu->startmenu->titre->text, sfBlack);
    sfText_setOutlineThickness(gamedata->menu->startmenu->titre->text, 3.0f);
}

static void fill_second_panel(gamedata_t *gamedata)
{
    gamedata->menu->startmenu->back = create_button(
        "assets/buttons/back(102x102).png", (sfIntRect){0, 0, 102, 102});
    gamedata->menu->startmenu->newsave = create_button(
        "assets/buttons/new(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->startmenu->load = create_button(
        "assets/buttons/load(202x77).png", (sfIntRect){0, 0, 202, 77});
}

static void fill_first_panel(gamedata_t *gamedata)
{
    gamedata->menu->startmenu->first_panel = create_sprite(
        "assets/buttons/start_menu(944x155).png", (sfIntRect){0, 0, 944, 155});
    gamedata->menu->startmenu->second_panel = create_sprite(
        "assets/buttons/play_menu(484x155).png", (sfIntRect){0, 0, 484, 155});
    gamedata->menu->startmenu->play = create_button(
        "assets/buttons/play(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->startmenu->settings = create_button(
        "assets/buttons/settings(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->startmenu->credits = create_button(
        "assets/buttons/credits(202x77).png", (sfIntRect){0, 0, 202, 77});
    gamedata->menu->startmenu->leave = create_button(
        "assets/buttons/leave(202x77).png", (sfIntRect){0, 0, 202, 77});
}

static void fill_action_button_startmenu(gamedata_t *gamedata)
{
    gamedata->menu->startmenu->settings->func = settings_button;
    gamedata->menu->startmenu->play->func = play_button;
    gamedata->menu->startmenu->credits->func = credit_button;
    gamedata->menu->startmenu->leave->func = leave_button;
    gamedata->menu->startmenu->back->func = back_button;
    gamedata->menu->startmenu->newsave->func = newsave_button;
    gamedata->menu->startmenu->load->func = load_button;
}

void fill_startmenu(gamedata_t *gamedata, config_t *config)
{
    (void)config;
    gamedata->menu = malloc(sizeof(menu_t));
    gamedata->menu->startmenu = malloc(sizeof(startmenu_t));
    set_title(gamedata);
    gamedata->menu->startmenu->background = create_sprite(
        "assets/sprites/menu_back.png", (sfIntRect){0, 0, 3022, 1700});
    sfSprite_scale(gamedata->menu->startmenu->background->sprite,
        (sfVector2f){0.635, 0.635});
    fill_first_panel(gamedata);
    fill_second_panel(gamedata);
    fill_action_button_startmenu(gamedata);
    gamedata->menu->startmenu->grayed =
        create_sprite("assets/buttons/grayed.png", (sfIntRect){0, 0, 202, 77});
}

static void fill_gamemenu_function(gamedata_t *gamedata)
{
    gamedata->menu->gamemenu->save->func = save_button;
    gamedata->menu->gamemenu->load->func = load_button_ingame_menu;
    gamedata->menu->gamemenu->quit->func = leave_button_ingame_menu;
    gamedata->menu->gamemenu->option->func = settings_button_ingame_menu;
    gamedata->menu->gamemenu->inventory->func = inventory_button;
    gamedata->menu->gamemenu->close->func = close_button_ingame_menu;
}

static void fill_scale_ingame_menu(gamedata_t *gamedata)
{
    sfVector2f scale = (sfVector2f){0.25, 0.25};

    sfSprite_setScale(gamedata->menu->gamemenu->panel->sprite, scale);
    sfSprite_setScale(gamedata->menu->gamemenu->save->sprite->sprite, scale);
    sfSprite_setScale(gamedata->menu->gamemenu->load->sprite->sprite, scale);
    sfSprite_setScale(gamedata->menu->gamemenu->quit->sprite->sprite, scale);
    sfSprite_setScale(gamedata->menu->gamemenu->option->sprite->sprite, scale);
    sfSprite_setScale(gamedata->menu->gamemenu->inventory->sprite->sprite,
        scale);
    sfSprite_setScale(gamedata->menu->gamemenu->back->sprite->sprite, scale);
    sfSprite_setScale(gamedata->menu->gamemenu->close->sprite->sprite, scale);
    fill_gamemenu_function(gamedata);
}

void fill_gamemenu(gamedata_t *gamedata, config_t *config)
{
    (void)config;
    fill_credit(gamedata);
    gamedata->menu->gamemenu = malloc(sizeof(gamemenu_t));
    gamedata->menu->gamemenu->panel = create_sprite(
        "assets/buttons/pause_menu(710x180).png", (sfIntRect){0, 0, 710, 180});
    gamedata->menu->gamemenu->save = create_button(
        "assets/buttons/save(102x102).png", (sfIntRect){0, 0, 102, 102});
    gamedata->menu->gamemenu->load = create_button(
        "assets/buttons/load(102x102).png", (sfIntRect){0, 0, 102, 102});
    gamedata->menu->gamemenu->quit = create_button(
        "assets/buttons/quit(102x102).png", (sfIntRect){0, 0, 102, 102});
    gamedata->menu->gamemenu->option = create_button(
        "assets/buttons/options(102x102).png", (sfIntRect){0, 0, 102, 102});
    gamedata->menu->gamemenu->inventory = create_button(
        "assets/buttons/inventory(102x102).png", (sfIntRect){0, 0, 102, 102});
    gamedata->menu->gamemenu->back = create_button(
        "assets/buttons/back(102x102).png", (sfIntRect){0, 0, 102, 102});
    gamedata->menu->gamemenu->close = create_button(
        "assets/buttons/close(102x102).png", (sfIntRect){0, 0, 102, 102});
    fill_scale_ingame_menu(gamedata);
}
