/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** swap_with_hang
*/

#include "rpg_header.h"

void texte_center(button_t *button, text_t *text)
{
    sfFloatRect buttonBounds =
        sfSprite_getGlobalBounds(button->sprite->sprite);
    sfFloatRect textBounds = sfText_getGlobalBounds(text->text);
    float textX = buttonBounds.left + (buttonBounds.width / 2.0f) -
        (textBounds.width / 2.0f);
    float textY = buttonBounds.top + (buttonBounds.height / 2.0f) -
        (textBounds.height / 2.0f);

    sfText_setPosition(text->text, (sfVector2f){textX, textY});
}
