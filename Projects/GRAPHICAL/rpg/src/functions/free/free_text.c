/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_text
*/

#include "rpg_header.h"

void free_text(text_t *text)
{
    sfFont_destroy(text->font);
    sfText_destroy(text->text);
    free(text->str);
    free(text);
}
