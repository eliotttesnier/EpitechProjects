/*
** EPITECH PROJECT, 2024
** jingle.c
** File description:
** jingle.c
*/

#include "include/my_paint_header.h"

static void destroy_jingle(sfSprite *sprite, sfTexture *texture)
{
    sfTexture_destroy(texture);
    sfSprite_destroy(sprite);
}

static void display_jingle(sfRenderWindow *win, sfSprite *back,
    sfSprite *bar, sfText *adv)
{
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawSprite(win, back, NULL);
    sfRenderWindow_drawSprite(win, bar, NULL);
    sfRenderWindow_drawText(win, adv, NULL);
    sfRenderWindow_display(win);
}

static void destroy_text(sfText *text, sfFont *font, sfClock *clock)
{
    sfText_destroy(text);
    sfFont_destroy(font);
    sfClock_destroy(clock);
}

static void jingle_events(sfRenderWindow *win, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(win, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(win);
    }
}

static float loading(sfClock *clock)
{
    sfTime time;

    time = sfClock_getElapsedTime(clock);
    if (time.microseconds > 10000) {
        sfClock_restart(clock);
        return ((rand() % 3) / 2);
    }
    return (0.0);
}

void init_text(sfText *adv, sfFont *font)
{
    sfText_setOutlineColor(adv, sfBlack);
    sfText_setFont(adv, font);
    sfText_setCharacterSize(adv, 50);
    sfText_setColor(adv, sfWhite);
    sfText_setStyle(adv, sfTextBold);
    sfText_setString(adv, "0");
}

void jingle_loop(sfRenderWindow *win, sfSprite *back, sfSprite *bar)
{
    sfEvent event;
    sfText *adv = sfText_create();
    sfFont *font = sfFont_createFromFile("assets/leadcoat.ttf");
    float advancement = 1.0;
    sfClock *clock = sfClock_create();
    int len = (int)sfRenderWindow_getSize(win).x;
    int wid = (int)sfRenderWindow_getSize(win).y;
    float pos = 0.00;

    init_text(adv, font);
    while (sfRenderWindow_isOpen(win) && advancement < 100) {
        pos = (float)(len * ((float)advancement / 100) - len);
        sfSprite_setPosition(bar, (sfVector2f){pos, 0.0});
        sfText_setPosition(adv, (sfVector2f){len / 2 - 50, wid / 2});
        sfText_setString(adv, my_strcat(my_int_to_str((int)advancement), "%"));
        advancement += loading(clock);
        jingle_events(win, &event);
        display_jingle(win, back, bar, adv);
    }
    destroy_text(adv, font, clock);
}

void exec_jingle(sfRenderWindow *win)
{
    sfTexture *background;
    sfSprite *back = sfSprite_create();
    sfTexture *loadbar;
    sfSprite *bar = sfSprite_create();

    background = sfTexture_createFromFile("assets/jingle.png", NULL);
    sfSprite_setTexture(back, background, sfFalse);
    loadbar = sfTexture_createFromFile("assets/loadbar.png", NULL);
    sfSprite_setTexture(bar, loadbar, sfFalse);
    sfSprite_setPosition(bar, (sfVector2f){-1920.00, 0.00});
    jingle_loop(win, back, bar);
    destroy_jingle(back, background);
    destroy_jingle(bar, loadbar);
}
