/*
** EPITECH PROJECT, 2023
** check_shots.c
** File description:
** check if a bird is shot
*/

#include <SFML/Audio.h>
#include "../header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

static void check_duck1(sfMouseButtonEvent *event, s_all_s *all_s, s_var *va)
{
    sfVector2f duck1_pos = sfSprite_getPosition(all_s->duck1.sprite);

    if (event->x < duck1_pos.x + 110 && event->x >= duck1_pos.x
        && event->y < duck1_pos.y + 110 && event->y >= duck1_pos.y) {
            va->duck1.x = -300;
            va->duck1.y = rand() % (451 - 20) + 20;
            va->duck1.speed = rand() % (10 - 5 + 1) +5;
            va->curr_streak += 1;
    }
}

static void check_duck2(sfMouseButtonEvent *event, s_all_s *all_s, s_var *va)
{
    sfVector2f duck2_pos = sfSprite_getPosition(all_s->duck2.sprite);

    if (event->x < duck2_pos.x + 110 && event->x >= duck2_pos.x
        && event->y < duck2_pos.y + 110 && event->y >= duck2_pos.y) {
            va->duck2.x = -300;
            va->duck2.y = rand() % (451 - 20) + 20;
            va->duck2.speed = rand() % (10 - 5 + 1) +5;
            va->curr_streak += 1;
    }
}

static void check_duck3(sfMouseButtonEvent *event, s_all_s *all_s, s_var *va)
{
    sfVector2f duck3_pos = sfSprite_getPosition(all_s->duck3.sprite);

    if (event->x < duck3_pos.x + 110 && event->x >= duck3_pos.x
        && event->y < duck3_pos.y + 110 && event->y >= duck3_pos.y) {
            va->duck3.x = -300;
            va->duck3.y = rand() % (451 - 20) + 20;
            va->duck3.speed = rand() % (10 - 5 + 1) +5;
            va->curr_streak += 1;
    }
}

static void check_duck4(sfMouseButtonEvent *event, s_all_s *all_s, s_var *va)
{
    sfVector2f duck4_pos = sfSprite_getPosition(all_s->duck4.sprite);

    if (event->x < duck4_pos.x + 110 && event->x >= duck4_pos.x
        && event->y < duck4_pos.y + 110 && event->y >= duck4_pos.y) {
            va->duck4.x = -300;
            va->duck4.y = rand() % (451 - 20) + 20;
            va->duck4.speed = rand() % (10 - 5 + 1) +5;
            va->curr_streak += 1;
    }
}

int check_shot(sfMouseButtonEvent *event, s_all_s *all_s, s_var *va)
{
    int streak = va->curr_streak;
    sfVector2f duck1_pos = sfSprite_getPosition(all_s->duck1.sprite);
    sfVector2f duck2_pos = sfSprite_getPosition(all_s->duck2.sprite);
    sfVector2f duck3_pos = sfSprite_getPosition(all_s->duck3.sprite);

    check_duck1(event, all_s, va);
    check_duck2(event, all_s, va);
    check_duck3(event, all_s, va);
    check_duck4(event, all_s, va);
    if (va->max_streak < va->curr_streak)
        va->max_streak = va->curr_streak;
    if (streak == va->curr_streak) {
        va->curr_streak = 0;
        va->bonus_heart = 0;
    }
    if (va->curr_streak > 5)
        va->score += 5;
    else
        va->score += va->curr_streak;
}
