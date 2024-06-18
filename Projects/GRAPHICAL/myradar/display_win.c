/*
** EPITECH PROJECT, 2023
** display
** File description:
** displays
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "header.h"

void display_towers(sfRenderWindow *win, all_lists *all_l)
{
    list_towers *copy = all_l->l_towers;

    while (copy != NULL) {
        if (all_l->hitbox == sfTrue) {
            sfRenderWindow_drawCircleShape(win, copy->area, NULL);
        }
        if (all_l->entities == sfTrue)
            sfRenderWindow_drawSprite(win, copy->towers, NULL);
        copy = copy->next;
    }
}

void display_planes(sfRenderWindow *win, all_lists *all_l)
{
    list_planes *copy = all_l->l_planes->next;

    while (copy != NULL) {
        if (copy->presence == sfTrue && all_l->hitbox)
            sfRenderWindow_drawRectangleShape(win, copy->hitbox, NULL);
        if (copy->presence == sfTrue && all_l->entities == sfTrue)
            sfRenderWindow_drawSprite(win, copy->plane, NULL);
        copy = copy->next;
    }
}

void display_win(sfRenderWindow *win, sfSprite *background, all_lists *all_l)
{
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawSprite(win, background, NULL);
    if (all_l->entities == sfTrue || all_l->hitbox == sfTrue) {
        display_planes(win, all_l);
        display_towers(win, all_l);
    }
    sfRenderWindow_drawText(win, all_l->text, NULL);
    sfRenderWindow_display(win);
}
