/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** is_on_item
*/

#include "rpg_header.h"

bool is_on_sprite(sprite_t *sprite, sfVector2f pix)
{
    sfFloatRect pos = sfSprite_getGlobalBounds(sprite->sprite);

    if (pix.x < pos.left || pix.x > pos.left + pos.width)
        return (false);
    if (pix.y < pos.top || pix.y > pos.top + pos.height)
        return (false);
    return (true);
}

static bool is_on_rect(sfVector2f pix, sfFloatRect rect)
{
    if (pix.x < rect.left || pix.x > rect.left + rect.width)
        return (false);
    if (pix.y < rect.top || pix.y > rect.top + rect.height)
        return (false);
    return (true);
}

int get_on_equip(equipment_t *equip, sfVector2f pix)
{
    if (equip->equiped[HELMET] != NULL)
        if (is_on_sprite(equip->sprites[HELMET], pix))
            return (HELMET);
    if (equip->equiped[CHEST] != NULL)
        if (is_on_sprite(equip->sprites[CHEST], pix))
            return (CHEST);
    if (equip->equiped[GLOVES] != NULL)
        if (is_on_sprite(equip->sprites[GLOVES], pix))
            return (GLOVES);
    if (equip->equiped[BOOTS] != NULL)
        if (is_on_sprite(equip->sprites[BOOTS], pix))
            return (BOOTS);
    if (equip->equiped[WEAPON] != NULL)
        if (is_on_sprite(equip->sprites[WEAPON], pix))
            return (WEAPON);
    return (-1);
}

int is_on_equip(gamedata_t *game, sfVector2f pix)
{
    sfVector2f center = sfView_getCenter(game->window->view);

    if (is_on_rect(pix, (sfFloatRect){center.x - 50, center.y + 25.5, 25, 25}))
        return (HELMET);
    if (is_on_rect(pix, (sfFloatRect){center.x + 25, center.y + 25.5, 25, 25}))
        return (CHEST);
    if (is_on_rect(pix, (sfFloatRect){center.x - 50, center.y + 74.5, 25, 25}))
        return (GLOVES);
    if (is_on_rect(pix, (sfFloatRect){center.x + 25, center.y + 74.5, 25, 25}))
        return (BOOTS);
    if (is_on_rect(pix, (sfFloatRect){center.x - 12.5, center.y + 50, 25, 25}))
        return (WEAPON);
    return (-1);
}

bool is_on_item(backpack_t *back, sfVector2f pix)
{
    sfFloatRect pos = sfSprite_getGlobalBounds(back->sprite->sprite);

    if (pix.x < pos.left || pix.x > pos.left + pos.width)
        return (false);
    if (pix.y < pos.top || pix.y > pos.top + pos.height)
        return (false);
    return (true);
}

bool is_on_button(button_t *button, sfVector2f pix)
{
    return (is_on_sprite(button->sprite, pix));
}
