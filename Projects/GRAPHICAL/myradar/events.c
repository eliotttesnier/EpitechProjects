/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main file
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"

void manage_key_pressed(sfKeyEvent *event, all_lists *all_l)
{
    if (event->code == sfKeyS)
        all_l->entities = !all_l->entities;
    if (event->code == sfKeyL)
        all_l->hitbox = !all_l->hitbox;
}

void manage_key_pressed_end(sfKeyEvent *event, sfRenderWindow *win)
{
    if (event->code == sfKeySpace)
        sfRenderWindow_close(win);
}

void analyse_events_end(sfRenderWindow *win, sfEvent *event, all_lists *all_l)
{
    while (sfRenderWindow_pollEvent(win, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(win);
        if (event->type == sfEvtKeyPressed)
            manage_key_pressed_end(&event->key, win);
    }
}

void analyse_events(sfRenderWindow *win, sfEvent *event, all_lists *all_l)
{
    while (sfRenderWindow_pollEvent(win, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(win);
        if (event->type == sfEvtKeyPressed)
            manage_key_pressed(&event->key, all_l);
    }
}
