/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main file
*/

#include <SFML/Audio.h>
#include "header.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

static void draw_texts(s_tdisplay *texts, sfRenderWindow *win)
{
    sfRenderWindow_drawText(win, texts->ammo.text, NULL);
    sfRenderWindow_drawText(win, texts->lives.text, NULL);
    sfRenderWindow_drawText(win, texts->curr_streak.text, NULL);
    sfRenderWindow_drawText(win, texts->max_streak.text, NULL);
    sfRenderWindow_drawText(win, texts->score.text, NULL);
    sfRenderWindow_drawText(win, texts->max_score.text, NULL);
}

static void draw_buttons(s_all_s *a, sfRenderWindow *win, s_tdisplay *t)
{
    sfRenderWindow_drawSprite(win, a->difficulty.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->volmusic.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->volsdef.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->diffdown.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->diffup.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->volmudown.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->volmusup.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->volefdown.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->volefup.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->play.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->leave.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->restart.sprite, NULL);
    sfRenderWindow_drawText(win, t->difficulty.text, NULL);
    sfRenderWindow_drawText(win, t->mus_volume.text, NULL);
    sfRenderWindow_drawText(win, t->sef_volume.text, NULL);
}

void display_window(s_all_s *a, s_tdisplay *t, sfRenderWindow *win, s_var *va)
{
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawSprite(win, a->back.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->duck1.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->duck2.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->duck3.sprite, NULL);
    sfRenderWindow_drawSprite(win, a->duck4.sprite, NULL);
    draw_texts(t, win);
    sfRenderWindow_drawSprite(win, a->shotgun.sprite, NULL);
    if (va->pause == sfTrue) {
        sfRenderWindow_drawSprite(win, a->pause.sprite, NULL);
        draw_buttons(a, win, t);
    }
    sfRenderWindow_display(win);
}

void game_loop(sfRenderWindow *win, int beg)
{
    s_tdisplay texts;
    sfEvent event;
    sfClock *clock_d = sfClock_create();
    sfClock *clock_move = sfClock_create();
    s_all_s all_s;
    s_var vars;

    fill_sounds(&vars.sounds);
    music(&vars.sounds);
    fill_text(&texts);
    fill_var(&vars, beg);
    fill_ducks(&all_s);
    while (sfRenderWindow_isOpen(win)) {
        move_ducks(&all_s, &vars, clock_move, win);
        animation(clock_d, &all_s, &vars);
        actualise_text(&texts, &vars);
        display_window(&all_s, &texts, win, &vars);
        analyse_events(&event, win, &vars, &all_s);
    }
}

int my_hunter(int ac, char **av)
{
    sfVideoMode mode = {1366, 768, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "MyHunter",
    sfResize | sfClose, NULL);
    sfCursor *cursor;

    cursor = sfCursor_createFromSystem(sfCursorCross);
    sfRenderWindow_setMouseCursor(window, cursor);
    sfRenderWindow_setFramerateLimit(window, 30);
    game_loop(window, 1);
    sfRenderWindow_destroy(window);
    return (0);
}

int main(int ac, char **av)
{
    if (ac > 1)
        return (readme(ac, av));
    return (my_hunter(ac, av));
}
