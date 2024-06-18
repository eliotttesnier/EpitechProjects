/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** dragndrop
*/

#include "rpg_header.h"

const int xp_s[39] = {
    5,
    15,
    25,
    50,
    75,
    5,
    15,
    25,
    50,
    75,
    5,
    15,
    25,
    50,
    75,
    5,
    15,
    25,
    50,
    75,
    5,
    15,
    25,
    50,
    75,
    5,
    15,
    25,
    50,
    75,
    5,
    15,
    25,
    50,
    75,
    5,
    5,
    20,
    10,
};

void consume_item(gamedata_t *game, backpack_t *back)
{
    play_sfx(game, SFX_EAT);
    game->inventory->stats->health += back->item->reg;
    if (game->inventory->stats->health >= game->inventory->stats->max_health)
        game->inventory->stats->health = game->inventory->stats->max_health;
    remove_in_back(game, back);
}

void inventory_consume(gamedata_t *game, sfVector2f pix)
{
    backpack_t *back = game->inventory->backpack;

    for (; back != NULL; back = back->next) {
        if (is_on_item(back, pix) && back->item->id >= 35) {
            consume_item(game, back);
            return;
        }
    }
}

void inventory_drag(gamedata_t *game, sfVector2f pix)
{
    backpack_t *back = game->inventory->backpack;
    equipment_t *equip = game->inventory->equipment;
    int item = get_on_equip(game->inventory->equipment, pix);

    if (item != -1) {
        play_sfx(game, SFX_INV);
        put_equip_to_hang(game, equip, item, pix);
        return;
    }
    for (; back != NULL; back = back->next) {
        if (is_on_item(back, pix)) {
            play_sfx(game, SFX_INV);
            put_to_hang(game, back, pix);
            return;
        }
    }
}

static void drop_on_item(gamedata_t *game, sfVector2f pix)
{
    backpack_t *back = game->inventory->backpack;

    for (; back != NULL; back = back->next) {
        if (is_on_item(back, pix)) {
            play_sfx(game, SFX_INV);
            insert_in_back(game, back);
            return;
        }
    }
    play_sfx(game, SFX_INV);
    remove_from_hang(game);
}

void inventory_drop(gamedata_t *game, sfVector2f pix)
{
    int item = is_on_equip(game, pix);

    if (item != -1) {
        play_sfx(game, SFX_INV);
        insert_in_equip(game, item);
        return;
    }
    if (is_on_trash(game, pix)) {
        play_sfx(game, SFX_INV);
        game->inventory->stats->xp += xp_s[game->inventory->hanging->item->id];
        game->inventory->hanging = NULL;
        return;
    }
    drop_on_item(game, pix);
}
