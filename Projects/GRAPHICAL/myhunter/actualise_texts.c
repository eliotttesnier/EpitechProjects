/*
** EPITECH PROJECT, 2023
** actualise_texts.c
** File description:
** actualises texts
*/

#include <SFML/Audio.h>
#include "header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

static void actualise_effvol(s_text *effvol, s_var *va)
{
    int len_int = my_len_nbr(va->voleff);
    int sk = va->voleff;
    char str[len_int + 2];

    for (int i = 0; i < len_int; i++) {
        str[i] = sk / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        sk = sk % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '.';
    str[len_int + 1] = '\0';
    sfText_setString(effvol->text, str);
}

static void actualise_musvol(s_text *musvol, s_var *va)
{
    int len_int = my_len_nbr(va->volmus);
    int sk = va->volmus;
    char str[len_int + 2];

    for (int i = 0; i < len_int; i++) {
        str[i] = sk / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        sk = sk % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '.';
    str[len_int + 1] = '\0';
    sfText_setString(musvol->text, str);
}

static void actualise_diff(s_text *diff, s_var *va)
{
    char beg[13] = "   BEGINNER\0";
    char inter[13] = "INTERMEDIATE\0";
    char exp[13] = "     EXPERT\0";

    if (va->diff == 1)
        sfText_setString(diff->text, beg);
    if (va->diff == 2)
        sfText_setString(diff->text, inter);
    if (va->diff == 3)
        sfText_setString(diff->text, exp);
}

static void actualise_score(s_text *score, s_var *va)
{
    int len_int = my_len_nbr(va->score);
    int sk = va->score;
    char str[len_int + 1];

    for (int i = 0; i < len_int; i++) {
        str[i] = sk / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        sk = sk % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '\0';
    sfText_setString(score->text, str);
}

static void actualise_maxscore(s_text *score, s_var *va)
{
    int len_int = my_len_nbr(va->max_score);
    int sk = va->max_score;
    char str[len_int + 1];

    for (int i = 0; i < len_int; i++) {
        str[i] = sk / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        sk = sk % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '\0';
    sfText_setString(score->text, str);
}

void actualise_maxstreak(s_text *streak, s_var *va)
{
    int len_int = my_len_nbr(va->max_streak);
    int sk = va->max_streak;
    char str[len_int + 1];

    for (int i = 0; i < len_int; i++) {
        str[i] = sk / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        sk = sk % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '\0';
    sfText_setString(streak->text, str);
}

void actualise_streak(s_text *streak, s_var *va)
{
    int len_int = my_len_nbr(va->curr_streak);
    int sk = va->curr_streak;
    char str[len_int + 1];

    for (int i = 0; i < len_int; i++) {
        str[i] = sk / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        sk = sk % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '\0';
    sfText_setString(streak->text, str);
}

void actualise_heart(s_text *lives, s_var *va)
{
    char str[2];

    str[0] = va->lives + 48;
    str[1] = '\0';
    sfText_setString(lives->text, str);
}

void actualise_ammo(s_text *ammo, s_var *va)
{
    char str[2];

    str[0] = va->bullets + 48;
    str[1] = '\0';
    sfText_setString(ammo->text, str);
}

void actualise_text(s_tdisplay *texts, s_var *va)
{
    actualise_ammo(&texts->ammo, va);
    actualise_heart(&texts->lives, va);
    actualise_streak(&texts->curr_streak, va);
    actualise_maxstreak(&texts->max_streak, va);
    actualise_score(&texts->score, va);
    actualise_diff(&texts->difficulty, va);
    actualise_musvol(&texts->mus_volume, va);
    actualise_effvol(&texts->sef_volume, va);
    actualise_maxscore(&texts->max_score, va);
}
