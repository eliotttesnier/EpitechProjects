/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** create_help_button
*/

#include "include/my_paint_header.h"

static l_dropmenu *add_a_button(l_dropmenu *help, char *asset, void (*f)(void))
{
    l_dropmenu *new = malloc(sizeof(l_dropmenu));

    new->extended = false;
    new->s_button = create_button(asset, f);
    new->next = help;
    help = new;
    return (help);
}

l_dropmenu *create_help_button(void)
{
    l_dropmenu *help = NULL;

    help = add_a_button(help, "ABOUT.png", NULL);
    help = add_a_button(help, "HELP2.png", NULL);
    help = add_a_button(help, "HELP.png", NULL);
    return (help);
}
