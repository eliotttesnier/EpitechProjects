/*
** EPITECH PROJECT, 2023
** sounds.c
** File description:
** every_functions related to sounds
*/

#include <SFML/Audio.h>
#include "../header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

void actualise_volume(s_var *va)
{
    sfSound_setVolume(va->sounds.empty.sound, (float)va->voleff);
    sfSound_setVolume(va->sounds.error.sound, (float)va->voleff);
    sfSound_setVolume(va->sounds.book.sound, (float)(va->voleff) * 0.3);
    sfSound_setVolume(va->sounds.reload.sound, (float)va->voleff);
    sfSound_setVolume(va->sounds.shotgun.sound, (float)va->voleff);
    sfSound_setVolume(va->sounds.button.sound, (float)va->voleff);
    sfSound_setVolume(va->sounds.music.sound, (float)va->volmus);
}

void reload_sound(s_sounds *sounds)
{
    sfSound_play(sounds->reload.sound);
}

void empty_shot(s_sounds *sounds)
{
    sfSound_play(sounds->empty.sound);
}

void shotgun_shot(s_sounds *sounds)
{
    sfSound_play(sounds->shotgun.sound);
}

void music(s_sounds *sounds)
{
    sfSound_setVolume(sounds->music.sound, 50.00);
    sfSound_play(sounds->music.sound);
}
