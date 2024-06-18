/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** game loading button fonction
*/

#include "rpg_header.h"

static void draw_key_bind_button_two(gamedata_t *gamedata)
{
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->inventory->button->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->attack->button->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->fire_spell->button->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->heal_spell->button->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->stun_spell->button->sprite->sprite, NULL);
}

void draw_key_bind_button(gamedata_t *gamedata)
{
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->forward->button->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->backward->button->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->left->button->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->right->button->sprite->sprite, NULL);
    sfRenderWindow_drawSprite(gamedata->window->window,
        gamedata->menu->optionmenu->interact->button->sprite->sprite, NULL);
    draw_key_bind_button_two(gamedata);
}
