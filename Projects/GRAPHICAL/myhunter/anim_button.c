/*
** EPITECH PROJECT, 2023
** anim_button.c
** File description:
** button animation
*/

#include "header.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>

static void anim_restart(sfRenderWindow *win, s_all_s *all_s)
{
    sfVector2f vector = sfSprite_getPosition(all_s->restart.sprite);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win);

    if (mouse.x < vector.x + 200 && mouse.x >= vector.x &&
        mouse.y < vector.y + 100 && mouse.y >= vector.y)
        all_s->restart.rect.left = 200;
    else
        all_s->restart.rect.left = 0;
    sfSprite_setTextureRect(all_s->restart.sprite, all_s->restart.rect);
}

static void anim_leave(sfRenderWindow *win, s_all_s *all_s)
{
    sfVector2f vector = sfSprite_getPosition(all_s->leave.sprite);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win);

    if (mouse.x < vector.x + 200 && mouse.x >= vector.x &&
        mouse.y < vector.y + 100 && mouse.y >= vector.y)
        all_s->leave.rect.left = 200;
    else
        all_s->leave.rect.left = 0;
    sfSprite_setTextureRect(all_s->leave.sprite, all_s->leave.rect);
}

static void anim_play(sfRenderWindow *win, s_all_s *all_s)
{
    sfVector2f vector = sfSprite_getPosition(all_s->play.sprite);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win);

    if (mouse.x < vector.x + 200 && mouse.x >= vector.x &&
        mouse.y < vector.y + 100 && mouse.y >= vector.y)
        all_s->play.rect.left = 200;
    else
        all_s->play.rect.left = 0;
    sfSprite_setTextureRect(all_s->play.sprite, all_s->play.rect);
}

void anim_d(sfRenderWindow *win, s_all_s *all_s)
{
    sfVector2f vdown = sfSprite_getPosition(all_s->diffdown.sprite);
    sfVector2f vup = sfSprite_getPosition(all_s->diffup.sprite);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win);

    if (mouse.x < vdown.x + 100 && mouse.x >= vdown.x &&
        mouse.y < vdown.y + 100 && mouse.y >= vdown.y) {
        all_s->diffdown.rect.left = 100;
    } else {
        all_s->diffdown.rect.left = 0;
    }
    if (mouse.x < vup.x + 100 && mouse.x >= vup.x &&
        mouse.y < vup.y + 100 && mouse.y >= vup.y) {
        all_s->diffup.rect.left = 100;
    } else {
        all_s->diffup.rect.left = 0;
    }
    sfSprite_setTextureRect(all_s->diffdown.sprite, all_s->diffdown.rect);
    sfSprite_setTextureRect(all_s->diffup.sprite, all_s->diffup.rect);
}

void anim_s(sfRenderWindow *win, s_all_s *all_s)
{
    sfVector2f vdown = sfSprite_getPosition(all_s->volefdown.sprite);
    sfVector2f vup = sfSprite_getPosition(all_s->volefup.sprite);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win);

    if (mouse.x < vdown.x + 100 && mouse.x >= vdown.x &&
        mouse.y < vdown.y + 100 && mouse.y >= vdown.y) {
        all_s->volefdown.rect.left = 100;
    } else {
        all_s->volefdown.rect.left = 0;
    }
    if (mouse.x < vup.x + 100 && mouse.x >= vup.x &&
        mouse.y < vup.y + 100 && mouse.y >= vup.y) {
        all_s->volefup.rect.left = 100;
    } else {
        all_s->volefup.rect.left = 0;
    }
    sfSprite_setTextureRect(all_s->volefdown.sprite, all_s->volefdown.rect);
    sfSprite_setTextureRect(all_s->volefup.sprite, all_s->volefup.rect);
}

void anim_m(sfRenderWindow *win, s_all_s *all_s)
{
    sfVector2f vdown = sfSprite_getPosition(all_s->volmudown.sprite);
    sfVector2f vup = sfSprite_getPosition(all_s->volmusup.sprite);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win);

    if (mouse.x < vdown.x + 100 && mouse.x >= vdown.x &&
        mouse.y < vdown.y + 100 && mouse.y >= vdown.y) {
        all_s->volmudown.rect.left = 100;
    } else {
        all_s->volmudown.rect.left = 0;
    }
    if (mouse.x < vup.x + 100 && mouse.x >= vup.x &&
        mouse.y < vup.y + 100 && mouse.y >= vup.y) {
        all_s->volmusup.rect.left = 100;
    } else {
        all_s->volmusup.rect.left = 0;
    }
    sfSprite_setTextureRect(all_s->volmudown.sprite, all_s->volmudown.rect);
    sfSprite_setTextureRect(all_s->volmusup.sprite, all_s->volmusup.rect);
}

void anim_button(sfRenderWindow *win, s_all_s *a)
{
    anim_d(win, a);
    anim_s(win, a);
    anim_m(win, a);
    anim_play(win, a);
    anim_leave(win, a);
    anim_restart(win, a);
}
