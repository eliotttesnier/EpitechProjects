/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** inventory_position
*/

#include "rpg_header.h"

static void backpack_position(gamedata_t *game, sfVector2f center)
{
    sfVector2f pos = (sfVector2f){center.x - (232.5), center.y - (127.5)};
    backpack_t *back = game->inventory->backpack;
    int count = 0;

    sfSprite_setPosition(game->inventory->backsprite->sprite, pos);
    pos.x += 10;
    pos.y += 10;
    for (; back != NULL; back = back->next) {
        sfSprite_setPosition(back->sprite->sprite, pos);
        pos.x += 25 + 10;
        count += 1;
        if (count == 4) {
            pos.x = center.x - (222.5);
            pos.y += 25 + 10;
            count = 0;
        }
    }
}

static void equip_position(gamedata_t *game, sfVector2f center)
{
    equipment_t *equip = game->inventory->equipment;
    sfVector2f pos = (sfVector2f){center.x - (75), center.y};

    sfSprite_setPosition(game->inventory->equipsprite->sprite, pos);
    if (equip->equiped[HELMET] != NULL)
        sfSprite_setPosition(equip->sprites[HELMET]->sprite,
            (sfVector2f){center.x - 50, center.y + 25.5});
    if (equip->equiped[CHEST] != NULL)
        sfSprite_setPosition(equip->sprites[CHEST]->sprite,
            (sfVector2f){center.x + 25, center.y + 25.5});
    if (equip->equiped[GLOVES] != NULL)
        sfSprite_setPosition(equip->sprites[GLOVES]->sprite,
            (sfVector2f){center.x - 50, center.y + 74.5});
    if (equip->equiped[BOOTS] != NULL)
        sfSprite_setPosition(equip->sprites[BOOTS]->sprite,
            (sfVector2f){center.x + 25, center.y + 74.5});
    if (equip->equiped[WEAPON] != NULL)
        sfSprite_setPosition(equip->sprites[WEAPON]->sprite,
            (sfVector2f){center.x - 12.5, center.y + 50});
}

static void preview_position(gamedata_t *game, sfVector2f center)
{
    preview_t *prev = game->inventory->preview;
    sfVector2f pos = (sfVector2f){center.x - (24), center.y - 85};

    sfSprite_setPosition(prev->not_worn[HELMET].sprite, pos);
    sfSprite_setPosition(prev->worn[HELMET].sprite, pos);
    sfSprite_setPosition(prev->not_worn[CHEST].sprite, pos);
    sfSprite_setPosition(prev->worn[CHEST].sprite, pos);
    sfSprite_setPosition(prev->not_worn[GLOVES].sprite, pos);
    sfSprite_setPosition(prev->worn[GLOVES].sprite, pos);
    sfSprite_setPosition(prev->not_worn[BOOTS].sprite, pos);
    sfSprite_setPosition(prev->worn[BOOTS].sprite, pos);
}

static void stats_position(gamedata_t *game, sfVector2f center)
{
    sfText_setPosition(game->inventory->atk->text,
        (sfVector2f){center.x - 75, center.y - 70});
    sfText_setPosition(game->inventory->def->text,
        (sfVector2f){center.x - 75, center.y - 30});
    sfText_setPosition(game->inventory->xp->text,
        (sfVector2f){center.x + 30, center.y - 70});
    sfText_setPosition(game->inventory->mana->text,
        (sfVector2f){center.x + 30, center.y - 30});
    sfText_setPosition(game->inventory->hp->text,
        (sfVector2f){center.x - 24, center.y - 110});
}

void hang_position(gamedata_t *game)
{
    sfVector2f pos;

    if (game->inventory->hanging == NULL)
        return;
    pos = get_pixcoord(game);
    sfSprite_setPosition(game->inventory->hanging->sprite->sprite,
        (sfVector2f){pos.x - 12.5, pos.y - 12.5});
}

void inventory_positions(gamedata_t *game)
{
    sfVector2f center = sfView_getCenter(game->window->view);
    sfVector2f skill = (sfVector2f){center.x + (82.5), center.y - (127.5)};

    backpack_position(game, center);
    equip_position(game, center);
    preview_position(game, center);
    stats_position(game, center);
    hang_position(game);
    sfSprite_setPosition(game->inventory->skillsprite->sprite, skill);
}
