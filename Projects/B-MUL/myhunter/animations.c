/*
** EPITECH PROJECT, 2023
** animations.c
** File description:
** animations related functions
*/

#include <SFML/Audio.h>
#include "header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

void move_rect(sfIntRect *rect, int offset, int max_value)
{
    int left = rect->left;

    left = left + offset;
    if (left >= max_value)
        left = left - max_value;
    rect->left = left;
}

void anim_shot(s_all_s *all_s, s_var *va)
{
    sfTime time;
    double animation_time;

    if (va->pause == sfTrue)
        return;
    time = sfClock_getElapsedTime(va->gun_anim);
    animation_time = time.microseconds / 50000.0;
    if (animation_time > 1.0) {
        all_s->shotgun.rect.left += 103;
        if (all_s->shotgun.rect.left == 412) {
            va->anim_gun = sfFalse;
            all_s->shotgun.rect.left = 0;
        }
        sfClock_restart(va->gun_anim);
    }
    sfSprite_setTextureRect(all_s->shotgun.sprite, all_s->shotgun.rect);
}

void animation(sfClock *clock, s_all_s *all_s, s_var *va)
{
    sfTime time;
    double animation_time;

    if (va->pause == sfTrue)
        return;
    time = sfClock_getElapsedTime(clock);
    animation_time = time.microseconds / 200000.0;
    if (animation_time > 1.0) {
        move_rect(&all_s->duck1.rect, 110, 330);
        move_rect(&all_s->duck2.rect, 110, 330);
        move_rect(&all_s->duck3.rect, 110, 330);
        move_rect(&all_s->duck4.rect, 110, 330);
        sfClock_restart(clock);
    }
    sfSprite_setTextureRect(all_s->duck2.sprite, all_s->duck2.rect);
    sfSprite_setTextureRect(all_s->duck1.sprite, all_s->duck1.rect);
    sfSprite_setTextureRect(all_s->duck3.sprite, all_s->duck1.rect);
    sfSprite_setTextureRect(all_s->duck4.sprite, all_s->duck1.rect);
}
