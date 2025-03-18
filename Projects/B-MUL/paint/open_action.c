/*
** EPITECH PROJECT, 2024
** open_action
** File description:
** open_action
*/

#include "include/my_paint_header.h"
#include "include/my_paint_macro.h"

static sfRenderWindow *create_open_window(sfText *text, sfFont *font)
{
    sfVideoMode mode = {960, 540, 32};
    sfRenderWindow *win;

    win = sfRenderWindow_create(mode, "open file", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(win, 60);
    sfText_setOutlineColor(text, sfBlack);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 40);
    sfText_setColor(text, sfWhite);
    sfText_setStyle(text, sfTextBold);
    sfText_setString(text, "0");
    return (win);
}

static void update_name(save_s *save_struct, int code)
{
    if (code == 8 && save_struct->ind != 0) {
        save_struct->ind -= 1;
        save_struct->name[save_struct->ind] = '\0';
    }
    if (code == 13)
        save_struct->verif = true;
    if (save_struct->ind > 19)
        return;
    if (code != 8 && code != 13 &&
        (IS_LETTER(code) == 1 || code == '.' || code == '_')) {
        save_struct->name[save_struct->ind] = code;
        save_struct->ind += 1;
        save_struct->name[save_struct->ind] = '\0';
    }
}

static void analyse_open_event(sfRenderWindow *win, sfEvent *event,
    save_s *save_struct)
{
    while (sfRenderWindow_pollEvent(win, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(win);
        if (event->type == sfEvtTextEntered)
            update_name(save_struct, event->text.unicode);
    }
}

static void display_open_as(sfRenderWindow *win, sfText *name, save_s *s)
{
    sfSprite *back = sfSprite_create();
    sfTexture *backtext = sfTexture_createFromFile("assets/saveas_board.png"
        , NULL);

    sfSprite_setTexture(back, backtext, sfFalse);
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawSprite(win, back, NULL);
    sfText_setPosition(name, (sfVector2f){190.0, 375.0});
    sfText_setString(name, s->name);
    sfRenderWindow_drawText(win, name, NULL);
    sfRenderWindow_display(win);
    sfSprite_destroy(back);
    sfTexture_destroy(backtext);
}

int try_to_open(char *name, save_s *save_struct)
{
    sfImage *new = sfImage_createFromFile(name);

    if (new != NULL) {
        sfImage_destroy(new);
        return (1);
    }
    save_struct->ind = 0;
    save_struct->name[0] = '\0';
    save_struct->verif = false;
    return (0);
}

int verif_name_open(save_s *save_struct)
{
    int i = my_strlen(save_struct->name) - 1;
    char *n = save_struct->name;

    if (save_struct->verif == false)
        return (0);
    if (i < 4) {
        save_struct->name[0] = '\0';
        save_struct->verif = false;
        save_struct->ind = 0;
        return (0);
    }
    if (n[i] == 'g' && n[i - 1] == 'n' && n[i - 2] == 'p' && n[i - 3] == '.')
        return (try_to_open(save_struct->name, save_struct));
    if (n[i] == 'g' && n[i - 1] == 'p' && n[i - 2] == 'j' && n[i - 3] == '.')
        return (try_to_open(save_struct->name, save_struct));
    save_struct->name[0] = '\0';
    save_struct->verif = false;
    save_struct->ind = 0;
    return (0);
}

void loop_open_as(sfRenderWindow *win, save_s *save_struct,
    sfText *name, s_workspace *work)
{
    l_image *cur = find_current(work)->layer_list;
    sfEvent event;

    while (sfRenderWindow_isOpen(win) && verif_name_open(save_struct) != 1) {
        analyse_open_event(win, &event, save_struct);
        display_open_as(win, name, save_struct);
    }
    if (!sfRenderWindow_isOpen(win))
        return;
    cur->image = sfImage_createFromFile(save_struct->name);
    work->title = my_strcat("my_paint : ", save_struct->name);
    sfText_destroy(name);
    sfRenderWindow_destroy(win);
    free(save_struct->name);
}

void open_action(s_workspace *work)
{
    sfText *name = sfText_create();
    sfFont *font = sfFont_createFromFile("assets/save.otf");
    sfRenderWindow *window = create_open_window(name, font);
    save_s save_struct = {NULL, 0, false};

    save_struct.name = malloc(sizeof(char) * 20);
    save_struct.name[0] = '\0';
    loop_open_as(window, &save_struct, name, work);
    sfFont_destroy(font);
}
