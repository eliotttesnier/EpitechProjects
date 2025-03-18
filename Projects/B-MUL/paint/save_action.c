/*
** EPITECH PROJECT, 2024
** save_action
** File description:
** save_action
*/

#include "include/my_paint_header.h"
#include "include/my_paint_macro.h"

static void free_save_as(sfImage *to_save, sfRenderWindow *win,
    save_s *s, sfText *name)
{
    sfImage_destroy(to_save);
    sfRenderWindow_destroy(win);
    free(s->name);
    sfText_destroy(name);
}

void replace_pixel(sfImage *to_save, sfImage *img, int x, int y)
{
    if (sfImage_getPixel(to_save, x, y).a != 0)
        return;
    sfImage_setPixel(to_save, x, y, sfImage_getPixel(img, x, y));
}

void fill_image(sfImage *to_save, l_image *layers)
{
    if (layers == NULL)
        return;
    for (int x = 0; x < 1381; x++) {
        for (int y = 0; y < 574; y++) {
            replace_pixel(to_save, layers->image, x, y);
        }
    }
    fill_image(to_save, layers->next);
}

static sfRenderWindow *create_save_window(sfText *text, sfFont *font)
{
    sfVideoMode mode = {960, 540, 32};
    sfRenderWindow *win;

    win = sfRenderWindow_create(mode, "save as", sfDefaultStyle, NULL);
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

void analyse_save_as_event(sfRenderWindow *win, sfEvent *event,
    save_s *save_struct)
{
    while (sfRenderWindow_pollEvent(win, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(win);
        if (event->type == sfEvtTextEntered)
            update_name(save_struct, event->text.unicode);
    }
}

int verif_name(save_s *save_struct)
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
        return (1);
    if (n[i] == 'g' && n[i - 1] == 'p' && n[i - 2] == 'j' && n[i - 3] == '.')
        return (1);
    save_struct->name[0] = '\0';
    save_struct->verif = false;
    save_struct->ind = 0;
    return (0);
}

static void display_save_as(sfRenderWindow *win, sfText *name, save_s *s)
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

static void loop_save_as(sfRenderWindow *win, save_s *save_struct,
    sfText *name, s_workspace *work)
{
    l_image *cur = find_current(work)->layer_list;
    sfImage *sav = sfImage_create(1381, 574);
    sfEvent event;

    sfImage_copyImage(sav, cur->image, 0, 0, (sfIntRect){0, 0, 0, 0}, sfFalse);
    fill_image(sav, cur->next);
    while (sfRenderWindow_isOpen(win) && verif_name(save_struct) != 1) {
        analyse_save_as_event(win, &event, save_struct);
        display_save_as(win, name, save_struct);
    }
    if (!sfRenderWindow_isOpen(win)) {
        free_save_as(sav, win, save_struct, name);
        return;
    }
    sfImage_saveToFile(sav, save_struct->name);
    work->title = my_strcat("my_paint : ", save_struct->name);
    free_save_as(sav, win, save_struct, name);
}

void save_as_action(s_workspace *work)
{
    sfText *name = sfText_create();
    sfFont *font = sfFont_createFromFile("assets/save.otf");
    sfRenderWindow *window = create_save_window(name, font);
    save_s save_struct = {NULL, 0, false};

    save_struct.name = malloc(sizeof(char) * 20);
    save_struct.name[0] = '\0';
    loop_save_as(window, &save_struct, name, work);
    sfFont_destroy(font);
}
