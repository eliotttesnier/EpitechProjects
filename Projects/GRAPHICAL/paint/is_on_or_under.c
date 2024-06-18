/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** is_on_or_under
*/

#include "include/my_paint_header.h"

bool is_under(l_dropmenu *menu, sfVector2f pixcoord)
{
    l_dropmenu *tmp = menu;

    tmp = tmp->next;
    while (tmp != NULL) {
        if (is_on_button(pixcoord, menu->s_button) == true)
            return (true);
        tmp = tmp->next;
    }
    return (false);
}
