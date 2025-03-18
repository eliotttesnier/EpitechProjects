/*
** EPITECH PROJECT, 2023
** filling_sounds.c
** File description:
** fill sounds variable
*/

#include <SFML/Audio.h>
#include "../header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

void fill_sounds2(s_sounds *sounds)
{
    sounds->book.buffer = sfSoundBuffer_createFromFile("audios/book.wav");
    sounds->book.sound = sfSound_create();
    sfSound_setBuffer(sounds->book.sound, sounds->book.buffer);
}

void fill_sounds(s_sounds *sounds)
{
    sounds->empty.buffer = sfSoundBuffer_createFromFile("audios/empty.wav");
    sounds->empty.sound = sfSound_create();
    sounds->shotgun.buffer = sfSoundBuffer_createFromFile("audios/shot.wav");
    sounds->shotgun.sound = sfSound_create();
    sounds->reload.buffer = sfSoundBuffer_createFromFile("audios/reload.wav");
    sounds->reload.sound = sfSound_create();
    sounds->music.buffer = sfSoundBuffer_createFromFile("audios/doom.wav");
    sounds->music.sound = sfSound_create();
    sounds->button.buffer = sfSoundBuffer_createFromFile("audios/button.wav");
    sounds->button.sound = sfSound_create();
    sounds->error.buffer = sfSoundBuffer_createFromFile("audios/error.wav");
    sounds->error.sound = sfSound_create();
    sfSound_setBuffer(sounds->error.sound, sounds->error.buffer);
    sfSound_setBuffer(sounds->empty.sound, sounds->empty.buffer);
    sfSound_setBuffer(sounds->shotgun.sound, sounds->shotgun.buffer);
    sfSound_setBuffer(sounds->reload.sound, sounds->reload.buffer);
    sfSound_setBuffer(sounds->music.sound, sounds->music.buffer);
    sfSound_setLoop(sounds->music.sound, sfTrue);
    sfSound_setBuffer(sounds->button.sound, sounds->button.buffer);
    fill_sounds2(sounds);
}
