/*
** EPITECH PROJECT, 2024
** use_tool
** File description:
** use_tool
*/

#include "include/my_paint_header.h"

l_action_queue *find_current(s_workspace *work)
{
    l_action_queue *temp = work->action_queue;

    while (temp != NULL) {
        if (temp->activated_state == true)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

void draw(s_workspace *work, sfVector2f pix, edition_menu *menu)
{
    l_action_queue *current = find_current(work);
    sfVector2f pos = (sfVector2f){pix.x - 485, pix.y - 285};
    sfImage *image = current->layer_list->image;

    if (menu->pen->next->s_button->state == CLICKED)
        draw_circle(image, pos, work->color, menu->pen_slid->thickness);
    else
        draw_square(image, pos, work->color, menu->pen_slid->thickness);
}

void erase(s_workspace *work, sfVector2f pix, edition_menu *menu)
{
    l_action_queue *current = find_current(work);
    sfVector2f pos = (sfVector2f){pix.x - 485, pix.y - 285};
    sfImage *image = current->layer_list->image;

    if (menu->eraser->next->s_button->state == CLICKED)
        draw_circle(image, pos, sfTransparent, menu->eraser_slid->thickness);
    else
        draw_square(image, pos, sfTransparent, menu->eraser_slid->thickness);
}

void select_tool(sfVector2f pix, edition_menu *menu)
{
    if (menu->selection->active == false) {
        menu->selection->begx = (int)pix.x;
        menu->selection->begy = (int)pix.y;
        menu->selection->active = true;
    }
    menu->selection->endx = (int)pix.x;
    menu->selection->endy = (int)pix.y;
}

static void fill(s_workspace *work, sfVector2f pix)
{
    l_image *tmp = find_current(work)->layer_list;

    fill_tool(tmp, work->color, pix.x - 485, pix.y - 285);
}

static bool is_on_canva(s_workspace *work, sfVector2f pix, edition_menu *menu)
{
    sfSprite *sprite = work->action_queue->layer_list->image_sprite;
    sfVector2f pos = sfSprite_getPosition(sprite);
    sfFloatRect size = sfSprite_getGlobalBounds(sprite);

    if (menu->eraser->extended == true)
        if (pix.x < 520 && pix.y < 465)
            return (false);
    if (menu->pen->extended == true)
        if (pix.x < 520 && pix.y < 365)
            return (false);
    if (pix.x > pos.x && pix.x < (pos.x + size.width) &&
        pix.y > pos.y && pix.y < (pos.y + size.height))
        return (true);
    return (false);
}

static void reset_selection(edition_menu *menu)
{
    if (menu->tool == SELECT)
        return;
    menu->selection->begx = 0;
    menu->selection->begy = 0;
    menu->selection->endx = 0;
    menu->selection->endy = 0;
}

void use_tool(s_menubar *menu, s_workspace *work, sfRenderWindow *win)
{
    sfVector2f pix;

    reset_selection(menu->edition);
    if (work->using_tool == false)
        return;
    pix = get_pixcoord(win);
    if (is_on_canva(work, pix, menu->edition) == false)
        return;
    if (menu->edition->tool == DRAW)
        return (draw(work, pix, menu->edition));
    if (menu->edition->tool == ERASE)
        return (erase(work, pix, menu->edition));
    if (menu->edition->tool == SELECT)
        return (select_tool(pix, menu->edition));
    if (menu->edition->tool == FILL)
        return (fill(work, pix));
}
