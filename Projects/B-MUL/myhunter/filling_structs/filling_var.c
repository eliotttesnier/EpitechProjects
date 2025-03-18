/*
** EPITECH PROJECT, 2023
** filling_var.c
** File description:
** used to fill var
*/

#include <SFML/Audio.h>
#include "../header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int sf_vol_calc(void)
{
    int file_desc = open("texts_files/sf_vol.txt", O_RDONLY);
    char *buff = malloc(5);

    read(file_desc, buff, 5);
    buff[5] = '\0';
    return (my_getnbr(buff, 0));
}

static int music_vol_calc(void)
{
    int file_desc = open("texts_files/music_vol.txt", O_RDONLY);
    char *buff = malloc(5);

    read(file_desc, buff, 5);
    buff[5] = '\0';
    return (my_getnbr(buff, 0));
}

int max_score_calc(void)
{
    int file_desc = open("texts_files/max_score.txt", O_RDONLY);
    char *buff = malloc(15);

    read(file_desc, buff, 15);
    buff[15] = '\0';
    return (my_getnbr(buff, 0));
}

int max_streak_calc(void)
{
    int file_desc = open("texts_files/max_streak.txt", O_RDONLY);
    char *buff = malloc(15);

    read(file_desc, buff, 15);
    buff[15] = '\0';
    return (my_getnbr(buff, 0));
}

void fill_var2(s_var *va)
{
    va->duck1.x = -200;
    va->duck1.y = rand() % (451);
    va->duck1.speed = rand() % (20 - 5 + 1) +5;
    va->duck2.x = -200;
    va->duck2.y = rand() % (451);
    va->duck2.speed = rand() % (20 - 5 + 1) +5;
    va->duck3.x = -200;
    va->duck3.y = rand() % (451);
    va->duck3.speed = rand() % (20 - 5 + 1) +5;
    va->duck4.x = -200;
    va->duck4.y = rand() % (451);
    va->duck4.speed = rand() % (20 - 5 + 1) +5;
}

void fill_var(s_var *va, int beg)
{
    if (beg == 1)
        va->pause = sfTrue;
    else
        va->pause = sfFalse;
    va->gun_anim = sfClock_create();
    va->anim_gun = sfFalse;
    va->bonus_heart = 0;
    va->max_streak = max_streak_calc();
    va->max_score = max_score_calc();
    va->curr_streak = 0;
    va->score = 0;
    va->lives = 3;
    va->bullets = 5;
    va->voleff = sf_vol_calc();
    va->volmus = music_vol_calc();
    va->diff = 1;
    fill_var2(va);
}
