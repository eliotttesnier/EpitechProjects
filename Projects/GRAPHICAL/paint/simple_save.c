/*
** EPITECH PROJECT, 2024
** simple_save
** File description:
** simple save
*/

#include "include/my_paint_header.h"

void simple_save(s_workspace *work, s_button *button)
{
    l_image *cur = find_current(work)->layer_list;
    sfImage *sav = sfImage_create(1381, 574);

    if (my_strcmp(work->title, "my_paint : *untitled") == 1) {
        save_as_action(work);
        return;
    }
    sfImage_copyImage(sav, cur->image, 0, 0, (sfIntRect){0, 0, 0, 0}, sfFalse);
    fill_image(sav, cur->next);
    sfImage_saveToFile(sav, my_strcut(work->title, 11, -1));
    button->state = STATIC;
}
