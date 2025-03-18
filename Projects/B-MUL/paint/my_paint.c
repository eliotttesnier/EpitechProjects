/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** my_paint
*/

#include "include/my_paint_header.h"
#include "include/my_paint_macro.h"

void set_position(s_menubar *menubar, s_workspace *workspace)
{
    set_menubar_position(menubar);
    set_workspace_position(workspace);
}

static void display_selection(sfRenderWindow *win, s_selection *select)
{
    int x = 0;
    int y = 0;

    x = select->begx - select->endx;
    y = select->begy - select->endy;
    sfRectangleShape_setSize(select->shape, (sfVector2f){-x, -y});
    sfRectangleShape_setPosition(select->shape,
        (sfVector2f){select->begx, select->begy});
    sfRenderWindow_drawRectangleShape(win, select->shape, NULL);
}

void display_window(sfRenderWindow *win, sfSprite *back,
    s_menubar *menubar, s_workspace *workspace)
{
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawSprite(win, back, NULL);
    display_workspace(win, workspace);
    display_menu_bar(win, menubar);
    display_cursor(win, menubar);
    if (menubar->edition->tool == SELECT)
        display_selection(win, menubar->edition->selection);
    sfRenderWindow_display(win);
}

void exec_loop(sfRenderWindow *win, s_menubar *menubar, s_workspace *workspace)
{
    sfTexture *background;
    sfSprite *back = sfSprite_create();
    sfEvent event;

    sfRenderWindow_setMouseCursorVisible(win, sfFalse);
    background = sfTexture_createFromFile("assets/PAINT_background.jpg", NULL);
    sfSprite_setTexture(back, background, sfFalse);
    set_position(menubar, workspace);
    while (sfRenderWindow_isOpen(win)) {
        analyse_events(win, &event, menubar, workspace);
        use_tool(menubar, workspace, win);
        actualise_image(workspace);
        display_window(win, back, menubar, workspace);
        do_all_actions(win, back, menubar, workspace);
    }
    sfTexture_destroy(background);
    sfSprite_destroy(back);
    destroy_paint(menubar, workspace);
}

int my_paint(bool jingle)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window;
    s_menubar *menu_bar = create_menubar();
    s_workspace *workspace = create_workspace();

    window = sfRenderWindow_create(mode, "my_paint", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    if (jingle == true)
        exec_jingle(window);
    exec_loop(window, menu_bar, workspace);
    sfRenderWindow_destroy(window);
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 1 && av[1] == NULL)
        return (my_paint(false));
    if (my_strcmp(av[1], "-j") == 1)
        return (my_paint(true));
    write(2, "No arguments needed.\n", 22);
    return (84);
}
