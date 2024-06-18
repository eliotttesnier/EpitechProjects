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
#include <stdio.h>

static int actu_not_radius(list_planes **plane)
{
    (*plane)->in_radius = sfFalse;
    return (0);
}

static int actu_in_radius(list_planes **plane)
{
    (*plane)->in_radius = sfTrue;
    return (0);
}

static int is_in_circle(list_planes **plane, list_towers *tow)
{
    list_towers *temp = tow;
    sfVector2f pos = sfSprite_getPosition((*plane)->plane);
    sfVector2f pos_tow;

    for (temp; temp != NULL; temp = temp->next) {
        pos_tow = sfSprite_getPosition(temp->towers);
        if (sqrt(pow((pos.x - pos_tow.x), 2) +
            pow((pos.y - pos_tow.y), 2)) <= temp->radius + 20)
            return (actu_in_radius(plane));
        if (sqrt(pow((pos.x - pos_tow.x - 20), 2) +
            pow((pos.y - pos_tow.y), 2)) <= temp->radius + 20)
            return (actu_in_radius(plane));
        if (sqrt(pow((pos.x - pos_tow.x - 20), 2) +
            pow((pos.y - pos_tow.y - 20), 2)) <= temp->radius + 20)
            return (actu_in_radius(plane));
        if (sqrt(pow((pos.x - pos_tow.x), 2) +
            pow((pos.y - pos_tow.y - 20), 2)) <= temp->radius + 20)
            return (actu_in_radius(plane));
    }
    return (actu_not_radius(plane));
}

void actualise_presence(sfClock *clock, list_planes **list, list_towers *tow)
{
    list_planes *copy = (*list)->next;
    sfTime time;
    double current;

    time = sfClock_getElapsedTime(clock);
    current = time.microseconds / 1000000;
    while (copy != NULL) {
        if (copy->presence == sfFalse && current >= copy->delay)
            copy->presence = sfTrue;
        is_in_circle(&copy, tow);
        copy = copy->next;
    }
}

static void end_loop(sfRenderWindow *win, all_lists *all_l, background_s *back)
{
    background_s end;
    sfEvent event;

    end.texture = sfTexture_createFromFile("assets/end.png", NULL);
    end.back = sfSprite_create();
    sfSprite_setTexture(end.back, end.texture, sfFalse);
    all_l->entities = sfFalse;
    all_l->hitbox = sfFalse;
    while (sfRenderWindow_isOpen(win)) {
        analyse_events_end(win, &event, all_l);
        sfRenderWindow_clear(win, sfBlack);
        sfRenderWindow_drawSprite(win, back->back, NULL);
        sfRenderWindow_drawSprite(win, end.back, NULL);
        sfRenderWindow_display(win);
    }
    sfSprite_destroy(end.back);
    sfTexture_destroy(end.texture);
}

void game_loop(sfRenderWindow *win, all_lists *all_l)
{
    background_s background;
    sfEvent event;

    background.texture = sfTexture_createFromFile("assets/back.png", NULL);
    background.back = sfSprite_create();
    sfSprite_setTexture(background.back, background.texture, sfFalse);
    while (sfRenderWindow_isOpen(win) && all_l->l_planes->next != NULL) {
        analyse_events(win, &event, all_l);
        actualise_presence(all_l->gtime, &all_l->l_planes, all_l->l_towers);
        move_planes(all_l);
        actualise_timer(all_l);
        display_win(win, background.back, all_l);
        check_cols(&all_l->l_planes);
        check_arrive(&all_l->l_planes);
    }
    end_loop(win, all_l, &background);
    free_struct(all_l, &background);
}

int myradar(int ac, char **av)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window;
    all_lists all_l;

    all_l.l_planes = NULL;
    all_l.l_towers = NULL;
    all_l.gtime = sfClock_create();
    all_l.mtime = sfClock_create();
    all_l.entities = sfTrue;
    all_l.hitbox = sfFalse;
    fill_timer(&all_l);
    fill_list(&all_l, av);
    window = sfRenderWindow_create(mode, "my_radar", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 600);
    game_loop(window, &all_l);
    sfClock_destroy(all_l.gtime);
    sfClock_destroy(all_l.mtime);
    sfRenderWindow_destroy(window);
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        write(2, "./my_radar: bad arguments : 0 given\nretry with -h\n", 50);
        return 84;
    }
    if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0')
        return (readme(ac, av));
    if (error_cases(av[1]) == 84)
        return (84);
    return (myradar(ac, av));
}
