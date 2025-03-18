/*
** EPITECH PROJECT, 2023
** timer.c
** File description:
** timer text
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"
#include <stdio.h>

void fill_timer(all_lists *all_l)
{
    all_l->font = sfFont_createFromFile("assets/font.TTF");
    all_l->text = sfText_create();
    all_l->len_timer = 1;
    sfText_setColor(all_l->text, sfWhite);
    sfText_setOutlineColor(all_l->text, sfBlack);
    sfText_setOutlineThickness(all_l->text, 5.00);
    sfText_setString(all_l->text, "Seconds : 0");
    sfText_setPosition(all_l->text, (sfVector2f){1730, 10});
    sfText_setFont(all_l->text, all_l->font);
}

void actualise_timer(all_lists *all_l)
{
    sfTime time = sfClock_getElapsedTime(all_l->gtime);
    int seconds = time.microseconds / 1000000;
    char text[50] = "Seconds : ";
    int len_seconds = my_len_nbr(seconds);

    for (int i = 10; i < len_seconds + 10; i++) {
        text[i] = seconds / pow(10, len_seconds - 1 - i + 10) + 48;
        seconds = seconds % (int)(pow(10, len_seconds -1 -i + 10));
    }
    text[len_seconds + 10] = '\0';
    sfText_setString(all_l->text, text);
    if (len_seconds > all_l->len_timer)
        sfText_move(all_l->text, (sfVector2f){-20, 0});
    all_l->len_timer = len_seconds;
    return;
}
