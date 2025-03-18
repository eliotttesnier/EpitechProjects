/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** my_paint_header
*/

#pragma once

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Window/Keyboard.h>
#include "../lib/my_lib.h"
#include "my_paint_macro.h"
#include "math.h"

extern const void *(*tool_arr[4]) (void *, void *, void *, void *);

typedef enum activated_tool {
    SELECT = 0,
    DRAW,
    ERASE,
    FILL
} act_tool;

typedef enum button_state {
    STATIC = 0,
    HOVER,
    CLICKED
} button_state;

typedef struct s_button {
    sfSprite **sprites;
    sfTexture **textures;
    enum button_state state;
    void (*action)(void);
} s_button;

typedef struct l_dropmenu {
    bool extended;
    s_button *s_button;
    struct l_dropmenu *next;
} l_dropmenu;

typedef struct s_slider {
    int thickness;
    bool active;
    sfSprite *dot;
    sfSprite *back;
    sfTexture *dot_text;
    sfTexture *back_text;
} s_slider;

typedef struct s_selection {
    bool active;
    int begx;
    int begy;
    int endx;
    int endy;
    sfRectangleShape *shape;
} s_selection;

typedef struct edition_menu {
    bool extended;
    act_tool tool;
    sfSprite **cursors;
    sfCircleShape *circle;
    sfRectangleShape *square;
    sfTexture **cu_textu;
    s_selection *selection;
    l_dropmenu *pen;
    l_dropmenu *eraser;
    s_slider *pen_slid;
    s_slider *eraser_slid;
    s_button *edition;
    s_button *select;
    s_button *fill;
} edition_menu;

typedef struct menu_bar {
    l_dropmenu *file;
    l_dropmenu *help;
    edition_menu *edition;
    s_button *undo;
    s_button *redo;
} s_menubar;

typedef struct s_image {
    int index;
    s_button *layer;
    sfImage *image;
    sfTexture *texture;
    sfSprite *image_sprite;
    struct s_image *next;
} l_image;

typedef struct action_queue {
    bool activated_state;
    l_image *layer_list;
    struct action_queue *next;
} l_action_queue;

typedef struct s_colors {
    sfSprite *palette;
    sfTexture *texture;
    s_button **colors;
} s_colors;

typedef struct work_space {
    char *title;
    bool using_tool;
    sfColor color;
    l_action_queue *action_queue;
    s_colors *color_palette;
    sfSprite *work_board;
    sfSprite *layer_board;
    sfTexture *work_texture;
    sfTexture *layer_texture;
} s_workspace;

typedef struct save_s {
    char *name;
    int ind;
    bool verif;
} save_s;

char *my_int_to_str(int nb);
int my_nbrlen(int nb);
int my_strlen(char *str);
int my_strcmp(char *str1, char *str2);
char *my_strcat(char *str, char *str2);
char *my_strcut(char *str, int i, int j);
void exec_jingle(sfRenderWindow *win);
void change_active_state(edition_menu *menu);
void check_sliders(edition_menu *menu, sfVector2f pix);
void move_sliders(sfRenderWindow *win, edition_menu *menu);
void analyse_events(sfRenderWindow *win, sfEvent *event, s_menubar *menubar,
    s_workspace *workspace);
s_menubar *create_menubar(void);
s_button *create_button(char *asset, void (*func)(void));
l_dropmenu *create_file_button(void);
l_dropmenu *create_help_button(void);
edition_menu *create_edition_button(void);
bool is_on_button(sfVector2f pixcoord, s_button *button);
sfVector2f get_pixcoord(sfRenderWindow *win);
void check_hover(s_menubar *, s_workspace *, sfRenderWindow *win);
void manage_mouse_click(sfRenderWindow *win,
    s_menubar *menubar, s_workspace *workspace);
void display_menu_bar(sfRenderWindow *win, s_menubar *menubar);
void set_menubar_position(s_menubar *menubar);
void set_button_pos(sfSprite **sprite, int x, int y);
void set_pos(sfSprite *sprite, int x, int y);
void set_workspace_position(s_workspace *workspace);
void display_workspace(sfRenderWindow *win, s_workspace *workspace);
void display_button(sfRenderWindow *win, sfSprite **buton, button_state state);
void display_list(sfRenderWindow *win, l_dropmenu *menu);
void display_workspace(sfRenderWindow *win, s_workspace *workspace);
void display_cursor(sfRenderWindow *win, s_menubar *menubar);
s_workspace *create_workspace(void);
void check_canva(s_workspace *work, sfVector2f pix);
void use_tool(s_menubar *menu, s_workspace *work, sfRenderWindow *win);
void destroy_paint(s_menubar *menubar, s_workspace *workspace);
bool is_on_or_under(l_dropmenu *, sfVector2f);
void actualise_image(s_workspace *work);
void draw_circle(sfImage *image, sfVector2f pix, sfColor color, int rayon);
void draw_square(sfImage *image, sfVector2f pix, sfColor color, int size);
void display_window(sfRenderWindow *win, sfSprite *back,
    s_menubar *menubar, s_workspace *workspace);
void free_action_queue(l_action_queue *action);
l_action_queue *create_action_queue(void);
void set_layer_button_pos(l_image *layer_list);
void swap_layers(s_workspace *work);
l_action_queue *find_current(s_workspace *work);
void open_action(s_workspace *work);
void save_as_action(s_workspace *work);
void fill_image(sfImage *to_save, l_image *layers);
void simple_save(s_workspace *work, s_button *but);
void replace_rectangle(edition_menu *menu, s_workspace *work, sfColor color);
void do_all_actions(sfRenderWindow *win, sfSprite *back,
    s_menubar *menu, s_workspace *work);
void fill_tool(l_image *image, sfColor color, int x, int y);
