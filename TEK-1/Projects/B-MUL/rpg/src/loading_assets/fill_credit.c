/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** fill_credit
*/

#include "rpg_header.h"

void fill_credit(gamedata_t *game)
{
    credit_menu_t *menu;

    game->menu->creditmenu = malloc(sizeof(credit_menu_t) * 1);
    menu = game->menu->creditmenu;
    menu->back = create_sprite("assets/sprites/menu_back.png",
        (sfIntRect){0, 0, 3022, 1700});
    sfSprite_scale(menu->back->sprite, (sfVector2f){0.635, 0.635});
    menu->backbutt = create_button("assets/buttons/back(102x102).png",
        (sfIntRect){0, 0, 102, 102});
    sfSprite_setPosition(menu->backbutt->sprite->sprite, (sfVector2f){25, 25});
    menu->display = create_sprite("assets/credits/credits.png",
        (sfIntRect){0, 0, 1920, 7560});
    sfSprite_setPosition(menu->display->sprite, (sfVector2f){0, 1080});
    menu->clock = sfClock_create();
}
