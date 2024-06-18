/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** create text
*/

#include "rpg_header.h"

text_t *recreate_text(text_t *old, char *path)
{
    text_t *new = malloc(sizeof(text_t));

    sfText_destroy(old->text);
    sfFont_destroy(old->font);
    free(old->str);
    free(old);
    new->font = sfFont_createFromFile(path);
    if (new->font == NULL)
        exit(84);
    new->text = sfText_create();
    if (new->text == NULL)
        exit(84);
    sfText_setFont(new->text, new->font);
    sfText_setString(new->text, "");
    return new;
}

text_t *create_text(char *path)
{
    text_t *new = malloc(sizeof(text_t));

    new->font = sfFont_createFromFile(path);
    if (new->font == NULL)
        exit(84);
    new->text = sfText_create();
    if (new->text == NULL)
        exit(84);
    sfText_setFont(new->text, new->font);
    sfText_setString(new->text, "");
    return new;
}

text_t *create_text_menu(char *path, char *text, sfVector2f pos,
    sfVector2f scale)
{
    text_t *text_tempo = malloc(sizeof(text_t));

    text_tempo->font = sfFont_createFromFile(path);
    if (text_tempo->font == NULL)
        exit(84);
    text_tempo->text = sfText_create();
    if (text_tempo->text == NULL)
        exit(84);
    sfText_setFont(text_tempo->text, text_tempo->font);
    sfText_setString(text_tempo->text, text);
    sfText_setScale(text_tempo->text, scale);
    sfText_setPosition(text_tempo->text, pos);
    sfText_setColor(text_tempo->text, sfBlack);
    return text_tempo;
}
