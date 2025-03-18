/*
** EPITECH PROJECT, 2023
** saves.c
** File description:
** saves everything
*/

#include <SFML/Audio.h>
#include "header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static void save_sf_vol(int sf_vol)
{
    int len_int = my_len_nbr(sf_vol);
    FILE *file_ptr = fopen("texts_files/sf_vol.txt", "wb");
    char str[len_int];
    int i;

    for (int i = 0; i < len_int; i++) {
        str[i] = sf_vol / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        sf_vol = sf_vol % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '\0';
    fwrite(str, 1, len_int, file_ptr);
    fclose(file_ptr);
}

static void save_music_vol(int music_vol)
{
    int len_int = my_len_nbr(music_vol);
    FILE *file_ptr = fopen("texts_files/music_vol.txt", "wb");
    char str[len_int];
    int i;

    for (int i = 0; i < len_int; i++) {
        str[i] = music_vol / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        music_vol = music_vol % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '\0';
    fwrite(str, 1, len_int, file_ptr);
    fclose(file_ptr);
}

static void save_max_score(int max_score)
{
    int len_int = my_len_nbr(max_score);
    FILE *file_ptr = fopen("texts_files/max_score.txt", "wb");
    char str[len_int];
    int i;

    for (int i = 0; i < len_int; i++) {
        str[i] = max_score / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        max_score = max_score % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '\0';
    fwrite(str, 1, len_int, file_ptr);
    fclose(file_ptr);
}

static void save_max_streak(int max_streak)
{
    int len_int = my_len_nbr(max_streak);
    FILE *file_ptr = fopen("texts_files/max_streak.txt", "wb");
    char str[len_int];
    int i;

    for (int i = 0; i < len_int; i++) {
        str[i] = max_streak / pfmy_compute_power_rec(10, len_int -1 -i) + 48;
        max_streak = max_streak % pfmy_compute_power_rec(10, len_int -1 -i);
    }
    str[len_int] = '\0';
    fwrite(str, 1, len_int, file_ptr);
    fclose(file_ptr);
}

void save(s_var *va)
{
    save_max_streak(va->max_streak);
    save_max_score(va->max_score);
    save_music_vol(va->volmus);
    save_sf_vol(va->voleff);
}
