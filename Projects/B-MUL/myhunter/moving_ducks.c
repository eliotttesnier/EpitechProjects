/*
** EPITECH PROJECT, 2023
** moving_ducks.c
** File description:
** moves ducks
*/

#include <SFML/Audio.h>
#include "header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

void move_duck1(s_sprite *duck, s_var *va)
{
    sfVector2f vector;

    vector.x = va->duck1.x;
    vector.y = va->duck1.y;
    sfSprite_setPosition(duck->sprite, vector);
    va->duck1.x += va->duck1.speed * va->diff;
    if (va->duck1.x > 1350) {
        va->duck1.x = -300;
        va->duck1.y = rand() % (451 - 20) + 20;
        va->duck1.speed = rand() % (10 - 5 + 1) +5;
        va->lives -= 1;
        va->curr_streak = 0;
        va->bonus_heart = 0;
    }
}

static void move_duck4(s_sprite *duck, s_var *va)
{
    sfVector2f vector;

    vector.x = va->duck4.x;
    vector.y = va->duck4.y;
    sfSprite_setPosition(duck->sprite, vector);
    va->duck4.x += va->duck4.speed * va->diff;
    if (va->duck4.x > 1350) {
        va->duck4.x = -300;
        va->duck4.y = rand() % (451 - 20) + 20;
        va->duck4.speed = rand() % (10 - 5 + 1) +5;
        va->lives -= 1;
        va->curr_streak = 0;
        va->bonus_heart = 0;
    }
}

void move_duck2(s_sprite *duck, s_var *va)
{
    sfVector2f vector;

    vector.x = 1350 - va->duck2.x;
    vector.y = va->duck2.y;
    sfSprite_setPosition(duck->sprite, vector);
    va->duck2.x += va->duck2.speed * va->diff;
    if (va->duck2.x > 1350) {
        va->duck2.x = -300;
        va->duck2.y = rand() % (451 - 20) + 20;
        va->duck2.speed = rand() % (10 - 5 + 1) +5;
        va->lives -= 1;
        va->curr_streak = 0;
        va->bonus_heart = 0;
    }
}

void move_duck3(s_sprite *duck, s_var *va)
{
    sfVector2f vector;

    vector.x = 1350 - va->duck3.x;
    vector.y = va->duck3.y;
    sfSprite_setPosition(duck->sprite, vector);
    va->duck3.x += va->duck3.speed * va->diff;
    if (va->duck3.x > 1350) {
        va->duck3.x = -300;
        va->duck3.y = rand() % (451 - 20) + 20;
        va->duck3.speed = rand() % (10 - 5 + 1) +5;
        va->lives -= 1;
        va->curr_streak = 0;
        va->bonus_heart = 0;
    }
}

void move_gun(s_all_s *all_s, sfRenderWindow *win)
{
    sfVector2f mouse;

    mouse.x = (float)sfMouse_getPositionRenderWindow(win).x - 70;
    mouse.y = 588.00;
    sfSprite_setPosition(all_s->shotgun.sprite, mouse);
}

void move_ducks(s_all_s *all_s, s_var *va, sfClock *clock, sfRenderWindow *w)
{
    sfTime time;
    double moving_time;

    if (va->pause == sfTrue)
        return;
    time = sfClock_getElapsedTime(clock);
    move_gun(all_s, w);
    moving_time = time.microseconds / 10000.0;
    if (moving_time > 1.0) {
        move_duck1(&all_s->duck1, va);
        move_duck2(&all_s->duck2, va);
        move_duck3(&all_s->duck3, va);
        move_duck4(&all_s->duck4, va);
        sfClock_restart(clock);
    }
}
