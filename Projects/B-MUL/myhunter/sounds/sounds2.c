/*
** EPITECH PROJECT, 2023
** sounds2.c
** File description:
** every_functions related to sounds
*/

#include <SFML/Audio.h>
#include "../header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

void book_sound(s_sounds *sounds)
{
    sfSound_play(sounds->book.sound);
}

void error_sound(s_sounds *sounds)
{
    sfSound_play(sounds->error.sound);
}

void button_sound(s_sounds *sounds)
{
    sfSound_play(sounds->button.sound);
}
