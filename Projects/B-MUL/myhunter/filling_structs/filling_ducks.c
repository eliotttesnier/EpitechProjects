/*
** EPITECH PROJECT, 2023
** filling_ducks.c
** File description:
** main file
*/

#include <SFML/Audio.h>
#include "../header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

const sfVector2f pos = {-200, -200};

static void fill_gameover(s_sprite *gameover)
{
    gameover->texture = sfTexture_createFromFile("pictures/over.png", NULL);
    gameover->sprite = sfSprite_create();
    sfSprite_setTexture(gameover->sprite, gameover->texture, sfTrue);
}

static void fill_shotgun(s_sprite *shotgun)
{
    sfVector2f vector = {650, 588};
    sfVector2f scale = {2, 2};

    shotgun->texture = sfTexture_createFromFile("pictures/shotgun.png", NULL);
    shotgun->sprite = sfSprite_create();
    shotgun->rect.top = 0;
    shotgun->rect.left = 0;
    shotgun->rect.width = 100;
    shotgun->rect.height = 100;
    sfSprite_setTexture(shotgun->sprite, shotgun->texture, sfTrue);
    sfSprite_setTextureRect(shotgun->sprite, shotgun->rect);
    sfSprite_setScale(shotgun->sprite, scale);
    sfSprite_setPosition(shotgun->sprite, vector);
}

static void fill_pause(s_sprite *pause)
{
    pause->texture = sfTexture_createFromFile("pictures/pause.png", NULL);
    pause->sprite = sfSprite_create();
    sfSprite_setTexture(pause->sprite, pause->texture, sfTrue);
}

static void fill_back(s_sprite *back)
{
    back->texture = sfTexture_createFromFile("pictures/back.png", NULL);
    back->sprite = sfSprite_create();
    sfSprite_setTexture(back->sprite, back->texture, sfTrue);
}

static void fill_duck4(s_sprite *duck1)
{
    duck1->texture = sfTexture_createFromFile("pictures/duck4.png", NULL);
    duck1->sprite = sfSprite_create();
    duck1->rect.top = 0;
    duck1->rect.left = 0;
    duck1->rect.width = 110;
    duck1->rect.height = 110;
    sfSprite_setTexture(duck1->sprite, duck1->texture, sfTrue);
    sfSprite_setPosition(duck1->sprite, pos);
}

void fill_duck1(s_sprite *duck1)
{
    duck1->texture = sfTexture_createFromFile("pictures/duck_sheet.png", NULL);
    duck1->sprite = sfSprite_create();
    duck1->rect.top = 0;
    duck1->rect.left = 0;
    duck1->rect.width = 110;
    duck1->rect.height = 110;
    sfSprite_setTexture(duck1->sprite, duck1->texture, sfTrue);
    sfSprite_setPosition(duck1->sprite, pos);
}

void fill_duck2(s_sprite *duck2)
{
    duck2->texture = sfTexture_createFromFile("pictures/duck2.png", NULL);
    duck2->sprite = sfSprite_create();
    duck2->rect.top = 0;
    duck2->rect.left = 0;
    duck2->rect.width = 110;
    duck2->rect.height = 110;
    sfSprite_setTexture(duck2->sprite, duck2->texture, sfTrue);
    sfSprite_setPosition(duck2->sprite, pos);
}

void fill_duck3(s_sprite *duck2)
{
    duck2->texture = sfTexture_createFromFile("pictures/duck3.png", NULL);
    duck2->sprite = sfSprite_create();
    duck2->rect.top = 0;
    duck2->rect.left = 0;
    duck2->rect.width = 110;
    duck2->rect.height = 110;
    sfSprite_setTexture(duck2->sprite, duck2->texture, sfTrue);
    sfSprite_setPosition(duck2->sprite, pos);
}

void fill_ducks(s_all_s *all_s)
{
    fill_gameover(&all_s->game_over);
    fill_shotgun(&all_s->shotgun);
    fill_pause(&all_s->pause);
    fill_back(&all_s->back);
    fill_duck1(&all_s->duck1);
    fill_duck2(&all_s->duck2);
    fill_duck3(&all_s->duck3);
    fill_duck4(&all_s->duck4);
    fill_menu(all_s);
}
