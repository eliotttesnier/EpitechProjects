/*
** EPITECH PROJECT, 2023
** events.c
** File description:
** manages events
*/

#include "header.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>

void reload(s_var *va)
{
    if (va->bullets < 5) {
        va->bullets = 5;
        reload_sound(&va->sounds);
    }
}

void manage_key_pressed(sfKeyEvent *event, sfRenderWindow *window, s_var *va)
{
    if (event->code == sfKeyR)
        reload(va);
    if (event->code == sfKeyEscape) {
        book_sound(&va->sounds);
        va->pause = !va->pause;
    }
}

void manage_mouse_click(sfMouseButtonEvent *event, s_var *va, s_all_s *all_s)
{
    if (va->pause == sfTrue)
        return;
    if (va->bullets != 0) {
        shotgun_shot(&va->sounds);
        va->anim_gun = sfTrue;
        sfClock_restart(va->gun_anim);
        all_s->shotgun.rect.left = 0;
        check_shot(event, all_s, va);
        va->bullets -= 1;
    } else {
        empty_shot(&va->sounds);
    }
    if (va->score > va->max_score)
        va->max_score = va->score;
}

static void bonus_heart(s_var *va)
{
    if (va->curr_streak >= 25 && va->lives < 5 && va->bonus_heart == 0) {
        va->lives += 1;
        va->bonus_heart = 1;
    }
}

static void death_events(sfRenderWindow *win, sfEvent *event, sfTime *time)
{
    while (sfRenderWindow_pollEvent(win, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(win);
            time->microseconds = 5000000;
        }
    }
}

static void death(sfRenderWindow *win, s_var *va, s_all_s *a, sfEvent *event)
{
    sfSoundBuffer *b = sfSoundBuffer_createFromFile("audios/laugh.wav");
    sfSound *s = sfSound_create();
    sfClock *clock = sfClock_create();
    sfTime time = sfClock_getElapsedTime(clock);

    sfSound_stop(va->sounds.music.sound);
    sfSound_setBuffer(s, b);
    sfSound_setVolume(s, va->voleff);
    sfSound_play(s);
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawSprite(win, a->game_over.sprite, NULL);
    while (time.microseconds / 5000000 < 1.00) {
        sfRenderWindow_display(win);
        time = sfClock_getElapsedTime(clock);
        death_events(win, event, &time);
    }
    sfSound_destroy(s);
    destroy_sprites(a);
    destroy_variables(va);
    game_loop(win, 1);
}

void analyse_events(sfEvent *event, sfRenderWindow *win, s_var *va, s_all_s *a)
{
    actualise_volume(va);
    anim_button(win, a);
    bonus_heart(va);
    if (va->lives <= 0)
        death(win, va, a, event);
    if (va->anim_gun == sfTrue)
        anim_shot(a, va);
    while (sfRenderWindow_pollEvent(win, event)) {
        if (event->type == sfEvtClosed) {
            sfRenderWindow_close(win);
            destroy_sprites(a);
            destroy_variables(va);
        }
        if (event->type == sfEvtMouseButtonPressed &&
            check_button(win, event, a, va) == 0) {
            manage_mouse_click(&event->mouseButton, va, a);
        }
        if (event->type == sfEvtKeyPressed)
            manage_key_pressed(&event->key, win, va);
    }
}
