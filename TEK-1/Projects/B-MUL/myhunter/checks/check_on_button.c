/*
** EPITECH PROJECT, 2023
** check_on_button.c
** File description:
** check if on a button
*/

#include "../header.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>

static int check_rest(sfRenderWindow *w, sfEvent *e, s_all_s *all_s, s_var *v)
{
    sfVector2f vec = sfSprite_getPosition(all_s->restart.sprite);

    if (e->mouseButton.x < vec.x + 200 && e->mouseButton.x >= vec.x &&
        e->mouseButton.y < vec.y + 100 && e->mouseButton.y >= vec.y) {
        sfSound_stop(v->sounds.music.sound);
        destroy_sprites(all_s);
        destroy_variables(v);
        game_loop(w, 0);
        return (1);
    }
    return (0);
}

static int check_leave(sfRenderWindow *w, sfEvent *e, s_all_s *all_s, s_var *v)
{
    sfVector2f vec = sfSprite_getPosition(all_s->leave.sprite);

    if (e->mouseButton.x < vec.x + 200 && e->mouseButton.x >= vec.x &&
        e->mouseButton.y < vec.y + 100 && e->mouseButton.y >= vec.y) {
        sfRenderWindow_close(w);
        destroy_sprites(all_s);
        destroy_variables(v);
        return (1);
    }
    return (check_rest(w, e, all_s, v));
}

static int check_play(sfRenderWindow *w, sfEvent *e, s_all_s *all_s, s_var *v)
{
    sfVector2f vec = sfSprite_getPosition(all_s->play.sprite);

    if (e->mouseButton.x < vec.x + 200 && e->mouseButton.x >= vec.x &&
        e->mouseButton.y < vec.y + 100 && e->mouseButton.y >= vec.y) {
        v->pause = sfFalse;
        return (1);
    }
    return (check_leave(w, e, all_s, v));
}

int check_d(sfRenderWindow *win, sfEvent *event, s_all_s *all_s, s_var *v)
{
    sfVector2f vdo = sfSprite_getPosition(all_s->diffdown.sprite);
    sfVector2f vup = sfSprite_getPosition(all_s->diffup.sprite);

    if (event->mouseButton.x < vdo.x + 100 && event->mouseButton.x >= vdo.x &&
        event->mouseButton.y < vdo.y + 100 && event->mouseButton.y >= vdo.y) {
        if (v->diff > 1) {
            v->diff -= 1;
            return (1);
        }
        return (2);
    }
    if (event->mouseButton.x < vup.x + 100 && event->mouseButton.x >= vup.x &&
        event->mouseButton.y < vup.y + 100 && event->mouseButton.y >= vup.y) {
        if (v->diff < 3) {
            v->diff += 1;
            return (1);
        }
        return (2);
    }
    return (0);
}

int check_s(sfRenderWindow *win, sfEvent *event, s_all_s *all_s, s_var *v)
{
    sfVector2f vdo = sfSprite_getPosition(all_s->volefdown.sprite);
    sfVector2f vup = sfSprite_getPosition(all_s->volefup.sprite);

    if (event->mouseButton.x < vdo.x + 100 && event->mouseButton.x >= vdo.x &&
        event->mouseButton.y < vdo.y + 100 && event->mouseButton.y >= vdo.y) {
        if (v->voleff > 9) {
            v->voleff -= 10;
            return (1);
        }
        return (2);
    }
    if (event->mouseButton.x < vup.x + 100 && event->mouseButton.x >= vup.x &&
        event->mouseButton.y < vup.y + 100 && event->mouseButton.y >= vup.y) {
        if (v->voleff < 91) {
            v->voleff += 10;
            return (1);
        }
        return (2);
    }
    return (0);
}

int check_m(sfRenderWindow *win, sfEvent *event, s_all_s *all_s, s_var *v)
{
    sfVector2f vdo = sfSprite_getPosition(all_s->volmudown.sprite);
    sfVector2f vup = sfSprite_getPosition(all_s->volmusup.sprite);

    if (event->mouseButton.x < vdo.x + 100 && event->mouseButton.x >= vdo.x &&
        event->mouseButton.y < vdo.y + 100 && event->mouseButton.y >= vdo.y) {
        if (v->volmus > 9) {
            v->volmus -= 10;
            return (1);
        }
        return (2);
    }
    if (event->mouseButton.x < vup.x + 100 && event->mouseButton.x >= vup.x &&
        event->mouseButton.y < vup.y + 100 && event->mouseButton.y >= vup.y) {
        if (v->volmus < 91) {
            v->volmus += 10;
            return (1);
        }
        return (2);
    }
    return (0);
}

int check_button(sfRenderWindow *win, sfEvent *event, s_all_s *a, s_var *v)
{
    int button = 0;

    if (v->pause == sfFalse)
        return (0);
    button += check_d(win, event, a, v);
    button += check_s(win, event, a, v);
    button += check_m(win, event, a, v);
    button += check_play(win, event, a, v);
    if (button == 1) {
        button_sound(&v->sounds);
        return (1);
    }
    if (button == 2) {
        error_sound(&v->sounds);
        return (1);
    }
    return (0);
}
