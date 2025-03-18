/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** is_on_trash
*/

#include "rpg_header.h"

bool is_on_trash(gamedata_t *game, sfVector2f pix)
{
    sfSprite *back = game->inventory->backsprite->sprite;
    sfFloatRect rect = sfSprite_getGlobalBounds(back);

    rect.top += 875 / 4;
    rect.height -= 875 / 4 + 10;
    rect.left += 450 / 4;
    rect.width -= 450 / 4 + 10;
    if (pix.x < rect.left || pix.x > rect.left + rect.width)
        return (false);
    if (pix.y < rect.top || pix.y > rect.top + rect.height)
        return (false);
    return (true);
}
