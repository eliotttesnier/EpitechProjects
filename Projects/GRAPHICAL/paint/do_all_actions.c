/*
** EPITECH PROJECT, 2024
** check_hover
** File description:
** check if is hover
*/

#include "include/my_paint_header.h"

void reset_layers(s_workspace *work, s_menubar *menu)
{
    free_action_queue(work->action_queue);
    work->action_queue = create_action_queue();
    set_workspace_position(work);
    menu->file->next->s_button->state = STATIC;
    work->title = my_strcat("my_paint : ", "*untitled");
}

static void analyse_about_event(sfRenderWindow *win, s_menubar *menu)
{
    sfEvent evt;

    while (sfRenderWindow_pollEvent(win, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(win);
        if (evt.type == sfEvtMouseButtonPressed)
            menu->help->next->next->s_button->state = STATIC;
    }
}

void display_about(sfRenderWindow *win, sfSprite *back,
    s_menubar *menu, s_workspace *work)
{
    sfSprite *sp = sfSprite_create();
    sfTexture *tx = sfTexture_createFromFile("assets/about_board.png", NULL);

    sfSprite_setTexture(sp, tx, sfFalse);
    sfSprite_setPosition(sp, (sfVector2f){660, 140});
    while (sfRenderWindow_isOpen(win) &&
        menu->help->next->next->s_button->state == CLICKED) {
        sfRenderWindow_clear(win, sfBlack);
        sfRenderWindow_drawSprite(win, back, NULL);
        display_workspace(win, work);
        display_menu_bar(win, menu);
        sfRenderWindow_drawSprite(win, sp, NULL);
        display_cursor(win, menu);
        sfRenderWindow_display(win);
        analyse_about_event(win, menu);
    }
    sfSprite_destroy(sp);
    sfTexture_destroy(tx);
}

static void analyse_help_event(sfRenderWindow *win, s_menubar *menu)
{
    sfEvent evt;

    while (sfRenderWindow_pollEvent(win, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(win);
        if (evt.type == sfEvtMouseButtonPressed)
            menu->help->next->s_button->state = STATIC;
    }
}

void display_help(sfRenderWindow *win, sfSprite *back,
    s_menubar *menu, s_workspace *work)
{
    sfSprite *sp = sfSprite_create();
    sfTexture *tx = sfTexture_createFromFile("assets/help_board.png", NULL);

    sfSprite_setTexture(sp, tx, sfFalse);
    sfSprite_setPosition(sp, (sfVector2f){660, 140});
    while (sfRenderWindow_isOpen(win) &&
        menu->help->next->s_button->state == CLICKED) {
        sfRenderWindow_clear(win, sfBlack);
        sfRenderWindow_drawSprite(win, back, NULL);
        display_workspace(win, work);
        display_menu_bar(win, menu);
        sfRenderWindow_drawSprite(win, sp, NULL);
        display_cursor(win, menu);
        sfRenderWindow_display(win);
        analyse_help_event(win, menu);
    }
    sfSprite_destroy(sp);
    sfTexture_destroy(tx);
}

void do_file_action(sfRenderWindow *win, s_menubar *menu, s_workspace *work)
{
    if (menu->file->next->s_button->state == CLICKED)
        reset_layers(work, menu);
    if (menu->file->next->next->s_button->state == CLICKED) {
        open_action(work);
        menu->file->next->next->s_button->state = STATIC;
    }
    if (menu->file->next->next->next->s_button->state == CLICKED)
        simple_save(work, menu->file->next->next->next->s_button);
    if (menu->file->next->next->next->next->s_button->state == CLICKED) {
        save_as_action(work);
        menu->file->next->next->next->next->s_button->state = STATIC;
    }
    sfRenderWindow_setTitle(win, work->title);
}

void do_all_actions(sfRenderWindow *win, sfSprite *back,
    s_menubar *menu, s_workspace *work)
{
    l_image *tmp;

    if (menu->help->next->s_button->state == CLICKED)
        display_help(win, back, menu, work);
    if (menu->help->next->next->s_button->state == CLICKED)
        display_about(win, back, menu, work);
    for (tmp = find_current(work)->layer_list; tmp != NULL; tmp = tmp->next) {
        if (tmp->layer->state == CLICKED) {
            swap_layers(work);
        }
    }
    do_file_action(win, menu, work);
}
