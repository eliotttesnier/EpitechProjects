/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

#pragma once

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include "myprintf/include/my.h"
    #include <math.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>

typedef struct background {
    sfTexture *texture;
    sfSprite *back;
} background_s;

typedef struct linked_list_planes {
    sfBool presence;
    sfBool exploded;
    sfBool in_radius;
    double incrX;
    double incrY;
    int ax;
    int ay;
    int speed;
    int delay;
    sfSprite *plane;
    sfTexture *texture;
    sfRectangleShape *hitbox;
    struct linked_list_planes *next;

} list_planes;

typedef struct linked_list_towers {
    sfVector2f pos;
    int radius;
    sfSprite *towers;
    sfTexture *texture;
    sfCircleShape *area;
    struct linked_list_towers *next;
} list_towers;

typedef struct all_lists {
    sfText *text;
    sfFont *font;
    int len_timer;
    sfClock *gtime;
    sfClock *mtime;
    sfBool hitbox;
    sfBool entities;
    list_planes *l_planes;
    list_towers *l_towers;
} all_lists;

typedef struct corner {
    sfIntRect area;
    list_planes **list;
} corner;

void actualise_timer(all_lists *all_l);

void check_cols(list_planes **planes);
int is_overlap(list_planes **p1, list_planes **p2);

void move_planes(all_lists *all_l);
void fill_list(all_lists *all_l, char **av);
void fill_timer(all_lists *all_l);
void display_win(sfRenderWindow *win, sfSprite *background, all_lists *all_l);
void analyse_events(sfRenderWindow *win, sfEvent *event, all_lists *all_l);
void check_arrive(list_planes **list);

void analyse_events_end(sfRenderWindow *win, sfEvent *event, all_lists *all_l);

void del_temp(list_planes **list);
void add_temp(list_planes **list);
void del(list_planes **list);
void free_struct(all_lists *all_l, background_s *back);

int error_cases(char *file);
int get_size(char *file);
int readme(int ac, char **av);
