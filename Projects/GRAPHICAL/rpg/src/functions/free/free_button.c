/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_button
*/

#include "rpg_header.h"

void free_big_toggle(big_toggle_t *toggle)
{
    free_sprite(toggle->toggle);
    free(toggle);
}

void free_keybind(key_bind_t *keybind)
{
    free_text(keybind->key);
    free_text(keybind->name);
    free_button(keybind->button);
    free(keybind);
}

void free_toggle(toggle_t *toggle)
{
    free_sprite(toggle->toggle);
    free(toggle);
}

void free_slider(slider_t *slider)
{
    free_sprite(slider->back);
    free_sprite(slider->dot);
    free(slider);
}

void free_button(button_t *button)
{
    free_sprite(button->sprite);
    free(button);
}
