/*
** EPITECH PROJECT, 2023
** fill_text.c
** File description:
** fill struct text
*/

#include <SFML/Audio.h>
#include "../header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

static void fill_effvol(s_text *effvol)
{
    sfVector2f vector;

    vector.x = 680;
    vector.y = 620;
    effvol->font = sfFont_createFromFile("fonts/SIXTY.TTF");
    effvol->text = sfText_create();
    sfText_setPosition(effvol->text, vector);
    sfText_setOutlineColor(effvol->text, sfBlack);
    sfText_setFont(effvol->text, effvol->font);
    sfText_setCharacterSize(effvol->text, 20);
    sfText_setColor(effvol->text, sfWhite);
    sfText_setStyle(effvol->text, sfTextBold);
    sfText_setString(effvol->text, "0");
}

static void fill_musvol(s_text *musvol)
{
    sfVector2f vector;

    vector.x = 680;
    vector.y = 520;
    musvol->font = sfFont_createFromFile("fonts/SIXTY.TTF");
    musvol->text = sfText_create();
    sfText_setPosition(musvol->text, vector);
    sfText_setOutlineColor(musvol->text, sfBlack);
    sfText_setFont(musvol->text, musvol->font);
    sfText_setCharacterSize(musvol->text, 20);
    sfText_setColor(musvol->text, sfWhite);
    sfText_setStyle(musvol->text, sfTextBold);
    sfText_setString(musvol->text, "0");
}

static void fill_diff(s_text *diff)
{
    sfVector2f vector;

    vector.x = 630;
    vector.y = 420;
    diff->font = sfFont_createFromFile("fonts/SIXTY.TTF");
    diff->text = sfText_create();
    sfText_setPosition(diff->text, vector);
    sfText_setOutlineColor(diff->text, sfBlack);
    sfText_setFont(diff->text, diff->font);
    sfText_setCharacterSize(diff->text, 20);
    sfText_setColor(diff->text, sfWhite);
    sfText_setStyle(diff->text, sfTextBold);
    sfText_setString(diff->text, "0");
}

static void fill_score(s_text *score)
{
    sfVector2f vector;

    vector.x = 150;
    vector.y = 683;
    score->font = sfFont_createFromFile("fonts/SIXTY.TTF");
    score->text = sfText_create();
    sfText_setPosition(score->text, vector);
    sfText_setOutlineColor(score->text, sfBlack);
    sfText_setFont(score->text, score->font);
    sfText_setCharacterSize(score->text, 35);
    sfText_setColor(score->text, sfWhite);
    sfText_setStyle(score->text, sfTextBold);
    sfText_setString(score->text, "0");
}

static void fill_maxscore(s_text *score)
{
    sfVector2f vector;

    vector.x = 220;
    vector.y = 723;
    score->font = sfFont_createFromFile("fonts/SIXTY.TTF");
    score->text = sfText_create();
    sfText_setPosition(score->text, vector);
    sfText_setOutlineColor(score->text, sfBlack);
    sfText_setFont(score->text, score->font);
    sfText_setCharacterSize(score->text, 35);
    sfText_setColor(score->text, sfWhite);
    sfText_setStyle(score->text, sfTextBold);
    sfText_setString(score->text, "0");
}

void fill_maxstreak(s_text *streak)
{
    sfVector2f vector;

    vector.x = 240;
    vector.y = 647;
    streak->font = sfFont_createFromFile("fonts/SIXTY.TTF");
    streak->text = sfText_create();
    sfText_setPosition(streak->text, vector);
    sfText_setOutlineColor(streak->text, sfBlack);
    sfText_setFont(streak->text, streak->font);
    sfText_setCharacterSize(streak->text, 35);
    sfText_setColor(streak->text, sfWhite);
    sfText_setStyle(streak->text, sfTextBold);
    sfText_setString(streak->text, "0");
}

void fill_streak(s_text *streak)
{
    sfVector2f vector;

    vector.x = 175;
    vector.y = 605;
    streak->font = sfFont_createFromFile("fonts/SIXTY.TTF");
    streak->text = sfText_create();
    sfText_setPosition(streak->text, vector);
    sfText_setOutlineColor(streak->text, sfBlack);
    sfText_setFont(streak->text, streak->font);
    sfText_setCharacterSize(streak->text, 35);
    sfText_setColor(streak->text, sfWhite);
    sfText_setStyle(streak->text, sfTextBold);
    sfText_setString(streak->text, "0");
}

void fill_heart(s_text *lives)
{
    sfVector2f vector;

    vector.x = 1000;
    vector.y = 670;
    lives->font = sfFont_createFromFile("fonts/horrendo.ttf");
    lives->text = sfText_create();
    sfText_setPosition(lives->text, vector);
    sfText_setOutlineColor(lives->text, sfBlack);
    sfText_setFont(lives->text, lives->font);
    sfText_setCharacterSize(lives->text, 75);
    sfText_setColor(lives->text, sfRed);
    sfText_setStyle(lives->text, sfTextBold);
    sfText_setString(lives->text, "3");
}

void fill_ammo(s_text *ammo)
{
    sfVector2f vector;

    vector.x = 1215;
    vector.y = 668;
    ammo->font = sfFont_createFromFile("fonts/horrendo.ttf");
    ammo->text = sfText_create();
    sfText_setPosition(ammo->text, vector);
    sfText_setOutlineColor(ammo->text, sfBlack);
    sfText_setFont(ammo->text, ammo->font);
    sfText_setCharacterSize(ammo->text, 75);
    sfText_setColor(ammo->text, sfRed);
    sfText_setStyle(ammo->text, sfTextBold);
    sfText_setString(ammo->text, "5");
}

void fill_text(s_tdisplay *tdis)
{
    fill_ammo(&tdis->ammo);
    fill_heart(&tdis->lives);
    fill_streak(&tdis->curr_streak);
    fill_maxstreak(&tdis->max_streak);
    fill_maxscore(&tdis->max_score);
    fill_score(&tdis->score);
    fill_diff(&tdis->difficulty);
    fill_musvol(&tdis->mus_volume);
    fill_effvol(&tdis->sef_volume);
}
