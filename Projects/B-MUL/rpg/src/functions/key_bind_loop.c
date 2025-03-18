/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** key_bind_loop
*/

#include "rpg_header.h"

static int key_bind_check_event(call_key_bind_t *arg, sfEvent event)
{
    if (event.type == sfEvtClosed) {
        sfRenderWindow_close(arg->game->window->window);
    }
    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == -1)
            return 1;
        sfText_setString(arg->keybind->key->text,
            key_code_to_string(event.key.code));
        texte_center(arg->keybind->button, arg->keybind->key);
        arg->game->settings->keys[arg->key_type] = event.key.code;
        return 1;
    }
    return 0;
}

static int key_bind_pollevent_loop(call_key_bind_t *arg, sfEvent event)
{
    while (sfRenderWindow_pollEvent(arg->game->window->window, &event)) {
        if (key_bind_check_event(arg, event) == 1) {
            return 1;
        }
    }
    return 0;
}

void key_bind_loop(call_key_bind_t *arg)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(arg->game->window->window)) {
        if (key_bind_pollevent_loop(arg, event) == 1) {
            return;
        }
    }
}
