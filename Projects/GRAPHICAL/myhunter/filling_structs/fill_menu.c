/*
** EPITECH PROJECT, 2023
** fill_menu.c
** File description:
** fill_menu
*/

#include <SFML/Audio.h>
#include "../header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

static void fill_restart(s_sprite *restart)
{
    sfVector2f vsprite = {400, 220};

    restart->texture = sfTexture_createFromFile("pictures/restart.png", NULL);
    restart->sprite = sfSprite_create();
    restart->rect.top = 0;
    restart->rect.left = 0;
    restart->rect.width = 200;
    restart->rect.height = 100;
    sfSprite_setTexture(restart->sprite, restart->texture, sfTrue);
    sfSprite_setTextureRect(restart->sprite, restart->rect);
    sfSprite_setPosition(restart->sprite, vsprite);
}

static void fill_leave(s_sprite *leave)
{
    sfVector2f vsprite = {800, 220};

    leave->texture = sfTexture_createFromFile("pictures/leave.png", NULL);
    leave->sprite = sfSprite_create();
    leave->rect.top = 0;
    leave->rect.left = 0;
    leave->rect.width = 200;
    leave->rect.height = 100;
    sfSprite_setTexture(leave->sprite, leave->texture, sfTrue);
    sfSprite_setTextureRect(leave->sprite, leave->rect);
    sfSprite_setPosition(leave->sprite, vsprite);
}

static void fill_play(s_sprite *play)
{
    sfVector2f vsprite = {600, 220};

    play->texture = sfTexture_createFromFile("pictures/play.png", NULL);
    play->sprite = sfSprite_create();
    play->rect.top = 0;
    play->rect.left = 0;
    play->rect.width = 200;
    play->rect.height = 100;
    sfSprite_setTexture(play->sprite, play->texture, sfTrue);
    sfSprite_setTextureRect(play->sprite, play->rect);
    sfSprite_setPosition(play->sprite, vsprite);
}

void fill_but2(s_sprite *but1)
{
    but1->texture = sfTexture_createFromFile("pictures/plusbutton.png", NULL);
    but1->sprite = sfSprite_create();
    but1->rect.top = 0;
    but1->rect.left = 0;
    but1->rect.width = 100;
    but1->rect.height = 100;
    sfSprite_setTexture(but1->sprite, but1->texture, sfTrue);
    sfSprite_setTextureRect(but1->sprite, but1->rect);
}

void fill_but1(s_sprite *but1)
{
    but1->texture = sfTexture_createFromFile("pictures/minusbutton.png", NULL);
    but1->sprite = sfSprite_create();
    but1->rect.top = 0;
    but1->rect.left = 0;
    but1->rect.width = 100;
    but1->rect.height = 100;
    sfSprite_setTexture(but1->sprite, but1->texture, sfTrue);
    sfSprite_setTextureRect(but1->sprite, but1->rect);
}

static void fill_buttons(s_sprite *sprite, s_sprite *sprite2, s_sprite *spri3)
{
    sfVector2f vsprite = {600, 370};
    sfVector2f vsprite2 = {600, 470};
    sfVector2f vsprite3 = {600, 570};

    sprite->texture = sfTexture_createFromFile("pictures/diff.png", NULL);
    sprite->sprite = sfSprite_create();
    sprite2->texture = sfTexture_createFromFile("pictures/musicvol.png", NULL);
    sprite2->sprite = sfSprite_create();
    spri3->texture = sfTexture_createFromFile("pictures/seffectvol.png", NULL);
    spri3->sprite = sfSprite_create();
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    sfSprite_setPosition(sprite->sprite, vsprite);
    sfSprite_setTexture(sprite2->sprite, sprite2->texture, sfTrue);
    sfSprite_setPosition(sprite2->sprite, vsprite2);
    sfSprite_setTexture(spri3->sprite, spri3->texture, sfTrue);
    sfSprite_setPosition(spri3->sprite, vsprite3);
}

static void set_positions(s_all_s *a)
{
    sfVector2f v1 = {500, 370};
    sfVector2f v2 = {800, 370};
    sfVector2f v3 = {500, 470};
    sfVector2f v4 = {800, 470};
    sfVector2f v5 = {500, 570};
    sfVector2f v6 = {800, 570};

    sfSprite_setPosition(a->diffdown.sprite, v1);
    sfSprite_setPosition(a->diffup.sprite, v2);
    sfSprite_setPosition(a->volmudown.sprite, v3);
    sfSprite_setPosition(a->volmusup.sprite, v4);
    sfSprite_setPosition(a->volefdown.sprite, v5);
    sfSprite_setPosition(a->volefup.sprite, v6);
}

void fill_menu(s_all_s *all_s)
{
    fill_but1(&all_s->volefdown);
    fill_but2(&all_s->volefup);
    fill_but1(&all_s->volmudown);
    fill_but2(&all_s->volmusup);
    fill_but1(&all_s->diffdown);
    fill_but2(&all_s->diffup);
    fill_buttons(&all_s->difficulty, &all_s->volmusic, &all_s->volsdef);
    set_positions(all_s);
    fill_play(&all_s->play);
    fill_leave(&all_s->leave);
    fill_restart(&all_s->restart);
}
