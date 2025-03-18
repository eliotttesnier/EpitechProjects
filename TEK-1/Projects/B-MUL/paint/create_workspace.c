/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** create_workspace
*/

#include "include/my_paint_header.h"

s_colors *create_color_palette(void)
{
    s_colors *color_p = malloc(sizeof(s_colors));
    sfSprite *sp = sfSprite_create();
    sfTexture *tx = sfTexture_createFromFile("assets/palette.png", NULL);

    sfSprite_setTexture(sp, tx, sfFalse);
    color_p->palette = sp;
    color_p->texture = tx;
    color_p->colors = malloc(sizeof(s_button *) * 9);
    color_p->colors[0] = create_button("white.png", NULL);
    color_p->colors[1] = create_button("black.png", NULL);
    color_p->colors[2] = create_button("red.png", NULL);
    color_p->colors[3] = create_button("blue.png", NULL);
    color_p->colors[4] = create_button("green.png", NULL);
    color_p->colors[5] = create_button("cyan.png", NULL);
    color_p->colors[6] = create_button("magenta.png", NULL);
    color_p->colors[7] = create_button("yellow.png", NULL);
    color_p->colors[8] = NULL;
    return (color_p);
}

static void create_a_image(l_image *new)
{
    sfImage *image = sfImage_createFromColor(1381, 574, sfTransparent);
    sfSprite *sp = sfSprite_create();
    sfTexture *tx = sfTexture_createFromImage(image, NULL);

    sfSprite_setTexture(sp, tx, sfFalse);
    new->image = image;
    new->image_sprite = sp;
    new->texture = tx;
}

static l_image *add_a_layer(l_image *list, char *asset)
{
    l_image *new = malloc(sizeof(l_image));
    static int i = 5;

    create_a_image(new);
    new->layer = create_button(asset, NULL);
    new->index = i;
    new->next = list;
    list = new;
    i--;
    return (new);
}

static l_image *create_first_layer_list(void)
{
    l_image *list = NULL;

    list = add_a_layer(list, "layer_5.png");
    list = add_a_layer(list, "layer_4.png");
    list = add_a_layer(list, "layer_3.png");
    list = add_a_layer(list, "layer_2.png");
    list = add_a_layer(list, "layer_1.png");
    return (list);
}

l_action_queue *create_action_queue(void)
{
    l_action_queue *first = malloc(sizeof(l_action_queue));

    first->activated_state = true;
    first->next = NULL;
    first->layer_list = create_first_layer_list();
    return (first);
}

void fill_board(s_workspace *work_space)
{
    sfSprite *workboard = sfSprite_create();
    sfSprite *layerboard = sfSprite_create();
    sfTexture *work = sfTexture_createFromFile("assets/board.png", NULL);
    sfTexture *layer = sfTexture_createFromFile("assets/layerboard.png", NULL);

    sfSprite_setTexture(workboard, work, sfFalse);
    sfSprite_setTexture(layerboard, layer, sfFalse);
    work_space->work_board = workboard;
    work_space->work_texture = work;
    work_space->layer_board = layerboard;
    work_space->layer_texture = layer;
}

s_workspace *create_workspace(void)
{
    s_workspace *work_space = malloc(sizeof(s_workspace));

    fill_board(work_space);
    work_space->title = my_strcat("my_paint : ", "*untitled");
    work_space->using_tool = false;
    work_space->color = sfWhite;
    work_space->action_queue = create_action_queue();
    work_space->color_palette = create_color_palette();
    work_space->color_palette->colors[0]->state = CLICKED;
    return (work_space);
}
