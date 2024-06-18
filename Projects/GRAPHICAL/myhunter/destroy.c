/*
** EPITECH PROJECT, 2023
** destroy.c
** File description:
** destroy everything
*/

#include <SFML/Audio.h>
#include "header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void destroy_variables(s_var *va)
{
    sfClock_destroy(va->gun_anim);
    sfSoundBuffer_destroy(va->sounds.error.buffer);
    sfSound_destroy(va->sounds.error.sound);
    sfSoundBuffer_destroy(va->sounds.shotgun.buffer);
    sfSound_destroy(va->sounds.shotgun.sound);
    sfSoundBuffer_destroy(va->sounds.reload.buffer);
    sfSound_destroy(va->sounds.reload.sound);
    sfSoundBuffer_destroy(va->sounds.empty.buffer);
    sfSound_destroy(va->sounds.empty.sound);
    sfSoundBuffer_destroy(va->sounds.music.buffer);
    sfSound_destroy(va->sounds.music.sound);
    sfSoundBuffer_destroy(va->sounds.button.buffer);
    sfSound_destroy(va->sounds.button.sound);
    sfSoundBuffer_destroy(va->sounds.book.buffer);
    sfSound_destroy(va->sounds.book.sound);
    save(va);
}

void destroy_sprites2(s_all_s *a)
{
    sfTexture_destroy(a->volefup.texture);
    sfSprite_destroy(a->volefup.sprite);
    sfTexture_destroy(a->volmudown.texture);
    sfSprite_destroy(a->volmudown.sprite);
    sfTexture_destroy(a->volmusup.texture);
    sfSprite_destroy(a->volmusup.sprite);
    sfTexture_destroy(a->diffdown.texture);
    sfSprite_destroy(a->diffdown.sprite);
    sfTexture_destroy(a->diffup.texture);
    sfSprite_destroy(a->diffup.sprite);
    sfTexture_destroy(a->volmusic.texture);
    sfSprite_destroy(a->volmusic.sprite);
    sfTexture_destroy(a->volsdef.texture);
    sfSprite_destroy(a->volsdef.sprite);
    sfTexture_destroy(a->difficulty.texture);
    sfSprite_destroy(a->difficulty.sprite);
    sfTexture_destroy(a->play.texture);
    sfSprite_destroy(a->play.sprite);
    sfTexture_destroy(a->leave.texture);
    sfSprite_destroy(a->leave.sprite);
}

void destroy_sprites(s_all_s *a)
{
    sfTexture_destroy(a->duck1.texture);
    sfSprite_destroy(a->duck1.sprite);
    sfTexture_destroy(a->duck2.texture);
    sfSprite_destroy(a->duck2.sprite);
    sfTexture_destroy(a->duck3.texture);
    sfSprite_destroy(a->duck3.sprite);
    sfTexture_destroy(a->duck4.texture);
    sfSprite_destroy(a->duck4.sprite);
    sfTexture_destroy(a->shotgun.texture);
    sfSprite_destroy(a->shotgun.sprite);
    sfTexture_destroy(a->back.texture);
    sfSprite_destroy(a->back.sprite);
    sfTexture_destroy(a->pause.texture);
    sfSprite_destroy(a->pause.sprite);
    sfTexture_destroy(a->volefdown.texture);
    sfSprite_destroy(a->volefdown.sprite);
    sfTexture_destroy(a->restart.texture);
    sfSprite_destroy(a->restart.sprite);
    destroy_sprites2(a);
}

void destroy_texts(s_tdisplay *tdisplay)
{
    sfFont_destroy(tdisplay->ammo.font);
    sfText_destroy(tdisplay->ammo.text);
    sfFont_destroy(tdisplay->lives.font);
    sfText_destroy(tdisplay->lives.text);
    sfFont_destroy(tdisplay->difficulty.font);
    sfText_destroy(tdisplay->difficulty.text);
    sfFont_destroy(tdisplay->mus_volume.font);
    sfText_destroy(tdisplay->mus_volume.text);
    sfFont_destroy(tdisplay->sef_volume.font);
    sfText_destroy(tdisplay->sef_volume.text);
    sfFont_destroy(tdisplay->curr_streak.font);
    sfText_destroy(tdisplay->curr_streak.text);
    sfFont_destroy(tdisplay->max_streak.font);
    sfText_destroy(tdisplay->max_streak.text);
    sfFont_destroy(tdisplay->score.font);
    sfText_destroy(tdisplay->score.text);
}

void destroy(s_tdisplay *tdisplay, s_all_s *a, s_var *va)
{
    destroy_texts(tdisplay);
    destroy_sprites(a);
    destroy_variables(va);
}
