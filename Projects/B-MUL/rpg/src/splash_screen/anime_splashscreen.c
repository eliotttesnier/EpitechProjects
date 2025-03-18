/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** anime_splashscreen
*/

#include "rpg_header.h"

static void analyse_splash_event(gamedata_t *gamedata, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(gamedata->window->window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(gamedata->window->window);
    }
}

void get_zoom_loop(gamedata_t *gamedata, splashscreen_t *splash)
{
    sfEvent event;

    sfSprite_setOrigin(splash->fondu_bg, (sfVector2f){960, 513});
    for (float i = 1; sfRenderWindow_isOpen(gamedata->window->window)
        && i < 200;) {
        analyse_splash_event(gamedata, &event);
        if (sfClock_getElapsedTime(splash->anime_clock).microseconds
            > 7500) {
            i = i * 1.01;
            sfClock_restart(splash->anime_clock);
        }
        sfSprite_setScale(splash->fondu_bg, (sfVector2f){i, i});
        sfSprite_setPosition(splash->fondu_bg, (sfVector2f){960, 513});
        sfRenderWindow_clear(gamedata->window->window, sfBlack);
        sfRenderWindow_drawSprite(gamedata->window->window,
            gamedata->menu->startmenu->background->sprite, NULL);
        sfRenderWindow_drawSprite(gamedata->window->window, splash->fondu_bg,
            NULL);
        sfRenderWindow_display(gamedata->window->window);
    }
}

void get_fondu_loop(gamedata_t *gamedata, splashscreen_t *splash)
{
    sfEvent event;

    for (int i = 0; sfRenderWindow_isOpen(gamedata->window->window)
        && i < 255;) {
        analyse_splash_event(gamedata, &event);
        if (sfClock_getElapsedTime(splash->anime_clock).microseconds
            > 5000) {
            i++;
            sfClock_restart(splash->anime_clock);
        }
        sfRenderWindow_clear(gamedata->window->window, sfBlack);
        sfSprite_setColor(splash->bg, (sfColor){0, 0, 0, 255 - i});
        sfRenderWindow_drawSprite(gamedata->window->window,
            gamedata->menu->startmenu->background->sprite, NULL);
        sfRenderWindow_drawSprite(gamedata->window->window, splash->bg, NULL);
        sfRenderWindow_drawSprite(gamedata->window->window, splash->fondu_bg,
            NULL);
        sfRenderWindow_display(gamedata->window->window);
    }
}

void get_pause_loop(gamedata_t *game, splashscreen_t *splash)
{
    sfEvent event;
    sfMusic *gega = sfMusic_createFromFile("assets/sfx/gegagedi.wav");

    if (!gega)
        exit(84);
    sfMusic_play(gega);
    for (float i = 0.01; sfRenderWindow_isOpen(game->window->window) &&
        i < 2;) {
        analyse_splash_event(game, &event);
        sfRenderWindow_clear(game->window->window, sfBlue);
        if (sfClock_getElapsedTime(splash->anime_clock).microseconds > 15000) {
            i += 0.01;
            sfClock_restart(splash->anime_clock);
        }
        sfRenderWindow_drawSprite(game->window->window, splash->bg, NULL);
        sfSprite_setScale(splash->logo, (sfVector2f){1, 1});
        sfSprite_setPosition(splash->logo, (sfVector2f){960, 540});
        sfRenderWindow_drawSprite(game->window->window, splash->logo, NULL);
        sfRenderWindow_display(game->window->window);
    }
}

gamedata_t *get_anime_loop(gamedata_t *gamedata, splashscreen_t *splash)
{
    sfEvent event;

    for (float i = 0.01; sfRenderWindow_isOpen(gamedata->window->window)
        && i < 1;) {
        analyse_splash_event(gamedata, &event);
        sfRenderWindow_clear(gamedata->window->window, sfBlue);
        if (sfClock_getElapsedTime(splash->anime_clock).microseconds > 5000) {
            i = i * 1.01;
            fill_gamedata(gamedata);
            sfClock_restart(splash->anime_clock);
        }
        sfSprite_setPosition(splash->logo, (sfVector2f){960, 540});
        sfSprite_setScale(splash->logo, (sfVector2f){i, i});
        sfRenderWindow_drawSprite(gamedata->window->window, splash->bg, NULL);
        sfRenderWindow_drawSprite(gamedata->window->window,
            splash->logo, NULL);
        sfRenderWindow_display(gamedata->window->window);
    }
    return (gamedata);
}

static splashscreen_t *get_splashscreen(void)
{
    splashscreen_t *splash = malloc(sizeof(splashscreen_t));

    splash->anime_clock = sfClock_create();
    splash->bg = sfSprite_create();
    splash->logo = sfSprite_create();
    splash->fondu_bg = sfSprite_create();
    splash->bg_text = sfTexture_createFromFile(
        "assets/sprites/splash_screen_start(1920x1080).png", NULL);
    splash->logo_text = sfTexture_createFromFile(
        "assets/sprites/nugget_splash_screen(432x390).png", NULL);
    splash->fondu_bg_text = sfTexture_createFromFile(
        "assets/sprites/splash_screen_end(1920x1080).png", NULL);
    if (splash->bg_text == NULL || splash->logo_text == NULL
        || splash->fondu_bg_text == NULL)
        exit(84);
    sfSprite_setTexture(splash->bg, splash->bg_text, sfFalse);
    sfSprite_setTexture(splash->logo, splash->logo_text, sfFalse);
    sfSprite_setTexture(splash->fondu_bg, splash->fondu_bg_text, sfFalse);
    return (splash);
}

static void destroy_splash(splashscreen_t *splash)
{
    sfSprite_destroy(splash->bg);
    sfTexture_destroy(splash->bg_text);
    sfSprite_destroy(splash->logo);
    sfTexture_destroy(splash->logo_text);
    sfSprite_destroy(splash->fondu_bg);
    sfTexture_destroy(splash->fondu_bg_text);
    sfClock_destroy(splash->anime_clock);
}

void anime_splashscreen(gamedata_t *gamedata)
{
    splashscreen_t *splash = get_splashscreen();

    printf("%sLoading assets...%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    sfSprite_setOrigin(splash->logo, (sfVector2f){216, 195});
    get_anime_loop(gamedata, splash);
    get_pause_loop(gamedata, splash);
    get_fondu_loop(gamedata, splash);
    get_zoom_loop(gamedata, splash);
    destroy_splash(splash);
    printf("%sAssets loaded successfully.\n%s", ANSI_COLOR_GREEN,
        ANSI_COLOR_RESET);
    free(splash);
}
