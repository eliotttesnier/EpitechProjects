/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** create_edition_button
*/

#include "include/my_paint_header.h"

s_slider *fill_slider(void)
{
    s_slider *slider = malloc(sizeof(s_slider));

    slider->active = false;
    slider->dot_text =
        sfTexture_createFromFile("assets/slider_cursor.png", NULL);
    slider->back_text = sfTexture_createFromFile("assets/slider.png", NULL);
    slider->dot = sfSprite_create();
    slider->back = sfSprite_create();
    sfSprite_setTexture(slider->dot, slider->dot_text, sfFalse);
    sfSprite_setTexture(slider->back, slider->back_text, sfFalse);
    return (slider);
}

void create_sliders(edition_menu *edition)
{
    edition->eraser_slid = fill_slider();
    edition->pen_slid = fill_slider();
    edition->eraser_slid->thickness = 50;
    edition->pen_slid->thickness = 50;
}

static l_dropmenu *add_a_button(l_dropmenu *list, char *asset, void (*f)(void))
{
    l_dropmenu *new = malloc(sizeof(l_dropmenu));

    new->extended = false;
    new->s_button = create_button(asset, f);
    new->next = list;
    list = new;
    return (list);
}

static void cursors_rest(edition_menu *edition, sfSprite **cursors)
{
    sfSprite_setScale(cursors[0], (sfVector2f){0.5, 0.5});
    sfSprite_setScale(cursors[1], (sfVector2f){0.15, 0.15});
    sfSprite_setScale(cursors[2], (sfVector2f){0.35, 0.35});
    sfSprite_setScale(cursors[3], (sfVector2f){0.35, 0.35});
    edition->circle = sfCircleShape_create();
    edition->square = sfRectangleShape_create();
    sfCircleShape_setOutlineColor(edition->circle, sfBlack);
    sfRectangleShape_setOutlineColor(edition->square, sfBlack);
    sfCircleShape_setFillColor(edition->circle, sfTransparent);
    sfRectangleShape_setFillColor(edition->square, sfTransparent);
    sfCircleShape_setOutlineThickness(edition->circle, 2.00);
    sfRectangleShape_setOutlineThickness(edition->square, 2.00);
}

void create_cursors(edition_menu *edition)
{
    sfSprite **cursors = malloc(sizeof(sfSprite *) * 4);
    sfTexture **textures = malloc(sizeof(sfTexture *) * 4);

    textures[0] = sfTexture_createFromFile("assets/cursor_select.png", NULL);
    textures[1] = sfTexture_createFromFile("assets/cursor_pen.png", NULL);
    textures[2] = sfTexture_createFromFile("assets/cursor_eraser.png", NULL);
    textures[3] = sfTexture_createFromFile("assets/cursor_fill.png", NULL);
    cursors[0] = sfSprite_create();
    cursors[1] = sfSprite_create();
    cursors[2] = sfSprite_create();
    cursors[3] = sfSprite_create();
    sfSprite_setTexture(cursors[0], textures[0], sfFalse);
    sfSprite_setTexture(cursors[1], textures[1], sfFalse);
    sfSprite_setTexture(cursors[2], textures[2], sfFalse);
    sfSprite_setTexture(cursors[3], textures[3], sfFalse);
    cursors_rest(edition, cursors);
    edition->cu_textu = textures;
    edition->cursors = cursors;
}

void fill_buttons(edition_menu *edition)
{
    edition->fill = create_button("FILL.png", NULL);
    edition->select = create_button("SELECT.png", NULL);
    edition->edition = create_button("EDITION.png", NULL);
}

static s_selection *create_selection(void)
{
    s_selection *select = malloc(sizeof(s_selection) * 1);

    select->active = false;
    select->begx = 0;
    select->begy = 0;
    select->endx = 0;
    select->endy = 0;
    select->shape = sfRectangleShape_create();
    sfRectangleShape_setOutlineColor(select->shape, sfBlack);
    sfRectangleShape_setOutlineThickness(select->shape, 2.00);
    sfRectangleShape_setFillColor(select->shape, sfTransparent);
    return (select);
}

edition_menu *create_edition_button(void)
{
    edition_menu *edition = malloc(sizeof(edition_menu));

    create_cursors(edition);
    edition->eraser = NULL;
    edition->pen = NULL;
    edition->eraser = add_a_button(edition->eraser, "SQUARE.png", NULL);
    edition->eraser = add_a_button(edition->eraser, "CIRCLE.png", NULL);
    edition->eraser = add_a_button(edition->eraser, "ERASER.png", NULL);
    edition->eraser->next->s_button->state = CLICKED;
    edition->pen = add_a_button(edition->pen, "SQUARE.png", NULL);
    edition->pen = add_a_button(edition->pen, "CIRCLE.png", NULL);
    edition->pen = add_a_button(edition->pen, "PEN.png", NULL);
    edition->pen->next->s_button->state = CLICKED;
    edition->extended = false;
    edition->tool = SELECT;
    fill_buttons(edition);
    create_sliders(edition);
    edition->selection = create_selection();
    return (edition);
}
