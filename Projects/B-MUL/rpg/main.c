/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** main
*/

#include "rpg_header.h"

const scene_loop_t scene_arr[8] = {
    start_menu_loop,
    game_loading_loop,
    game_loop,
    ingame_menu_loop,
    inventory_loop,
    settings_menu_loop,
    credits_menu_loop,
    over_loop,
};

void execute_scene_loop(gamedata_t *gamedata, sfEvent *event)
{
    scene_arr[gamedata->scene](gamedata, event);
}

static sfImage *create_image(char *path)
{
    sfImage *image = sfImage_createFromFile(path);

    if (!image) {
        exit(84);
    }
    return (image);
}

window_t *get_window_struct(void)
{
    window_t *new = malloc(sizeof(window_t));

    printf("%sOpening window...\n%s", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    new->resolution = (sfVideoMode){1920, 1080, 32};
    new->window = sfRenderWindow_create(new->resolution,
        "The Legend of Damopies", sfResize | sfClose, NULL);
    new->fullscreen = sfFalse;
    new->icon = (sfUint8 *)sfImage_getPixelsPtr(
        create_image("assets/sprites/icon.png"));
    sfRenderWindow_setIcon(new->window, 100, 100,
        new->icon);
    new->view = sfView_create();
    sfRenderWindow_setFramerateLimit(new->window, FRAMERATE);
    printf("%sWindow successfully opened.\n%s", ANSI_COLOR_GREEN,
        ANSI_COLOR_RESET);
    return (new);
}

int main(void)
{
    gamedata_t *gamedata = malloc(sizeof(gamedata_t));
    sfEvent event;

    gamedata->window = get_window_struct();
    anime_splashscreen(gamedata);
    gamedata->scene = S_START_MENU;
    gamedata->adv = 0;
    while (sfRenderWindow_isOpen(gamedata->window->window)) {
        execute_scene_loop(gamedata, &event);
    }
    printf("%sClosing window...\n%s", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    free_gamedata(gamedata, false);
    printf("%sWindow successfully closed.\n%s", ANSI_COLOR_GREEN,
        ANSI_COLOR_RESET);
    return (0);
}
