/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** create_file_drop_menu
*/

#include "include/my_paint_header.h"

static l_dropmenu *add_a_button(l_dropmenu *file, char *asset, void (*f)(void))
{
    l_dropmenu *new = malloc(sizeof(l_dropmenu));

    new->extended = false;
    new->s_button = create_button(asset, f);
    new->next = file;
    file = new;
    return (file);
}

l_dropmenu *create_file_button(void)
{
    l_dropmenu *file = NULL;

    file = add_a_button(file, "SAVEAS.png", NULL);
    file = add_a_button(file, "SAVE.png", NULL);
    file = add_a_button(file, "OPEN.png", NULL);
    file = add_a_button(file, "NEW.png", NULL);
    file = add_a_button(file, "FILE.png", NULL);
    return (file);
}
