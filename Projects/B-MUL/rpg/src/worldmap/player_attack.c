/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** player_attack
*/

#include "rpg_header.h"

const int xp_drop[3] = {
    10,
    20,
    50
};

void check_attack(gamedata_t *game)
{
    player_t *player = game->entity->player;
    float time = sfClock_getElapsedTime(player->fight->buffer).microseconds;

    if (time > 350000)
        player->fight->can_attack = true;
    else
        player->fight->can_attack = false;
    if (player->fight->attacking == false)
        return;
}

static void play_good_sfx(gamedata_t *game, ennemy_t *eny)
{
    eny_t type = get_eny_type(eny);

    if (type == GOLEM)
        play_sfx(game, SFX_GODEATH);
    if (type == WOLF)
        play_sfx(game, SFX_WDEATH);
    if (type == GOBLIN)
        play_sfx(game, SFX_GDEATH);
}

void deal_dammage(gamedata_t *game, ennemy_t *eny)
{
    sfSprite_setColor(eny->sprite->sprite, sfRed);
    eny->hp -= game->inventory->stats->attack;
    if (eny->hp <= 0) {
        game->inventory->stats->xp += xp_drop[get_eny_type(eny)];
        drop_item(game, eny);
        play_good_sfx(game, eny);
        eny->alive = false;
        sfClock_restart(eny->respawn);
    }
}

void damage_ennemy(gamedata_t *game)
{
    ennemy_t *eny = game->entity->ennemy;

    for (; eny != NULL; eny = eny->next) {
        if (!eny->alive)
            continue;
        if (!is_eny_visible(game, eny))
            continue;
        if (!is_in_eny_range(game, eny))
            continue;
        deal_dammage(game, eny);
    }
}

static void attack_sfx(gamedata_t *game)
{
    item_t *item = game->inventory->equipment->equiped[WEAPON];

    if (item->id >= 0 && item->id <= 4)
        play_sfx(game, SFX_SWORD);
    if (item->id >= 5 && item->id <= 9)
        play_sfx(game, SFX_SPEAR);
    if (item->id >= 10 && item->id <= 14)
        play_sfx(game, SFX_AXE);
}

void player_attack(gamedata_t *game)
{
    if (game->entity->player->fight->can_attack == false)
        return;
    game->entity->player->fight->attacking = true;
    attack_sfx(game);
    sfClock_restart(game->entity->player->fight->buffer);
    sfClock_restart(game->entity->player->animation->clock);
    damage_ennemy(game);
}
