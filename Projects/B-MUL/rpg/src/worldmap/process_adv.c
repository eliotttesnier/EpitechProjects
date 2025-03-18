/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** process_adv
*/

#include "rpg_header.h"

static bool killed_golem(gamedata_t *game)
{
    if (is_eny_killed(game, 3))
        return (true);
    return (false);
}

static bool killed_wolves(gamedata_t *game)
{
    if (is_eny_killed(game, 0) && is_eny_killed(game, 2) &&
        is_eny_killed(game, 2))
        return (true);
    return (false);
}

static bool entered_mine(gamedata_t *game)
{
    sfVector2f position = game->entity->player->position;

    if (position.x > 1991 && position.x < 2088 &&
        position.y > 797 && position.y < 938)
        return (true);
    return (false);
}

void process_adv_second(gamedata_t *game)
{
    if (killed_golem(game) && game->adv == TALK_MINER) {
        game->adv = KILL_GOLEM;
        put_popup(game, "The golem is dead, you can now enter the mines");
    }
    if (game->adv == KILL_GOLEM && entered_mine(game))
        game->adv = ENTER_MINES;
    if (game->adv == ENTER_MINES && opened_chest(game, 16) &&
        opened_chest(game, 17))
        game->adv = FIND_CHESTS;
    if (game->adv == FIND_CHESTS && is_eny_killed(game, 13) &&
        is_eny_killed(game, 14))
        game->adv = TALK_DAMOPIES_END;
}

void process_adv(gamedata_t *game)
{
    if (talked_to_pnj(game, 0) && game->adv == WAKEUP)
        game->adv = TALK_BEACHMAN;
    if (opened_chest(game, 0) && game->adv == TALK_BEACHMAN)
        game->adv = OPEN_CHEST;
    if (talked_to_pnj(game, 1) && game->adv == OPEN_CHEST)
        game->adv = TALK_BRIDGEMAN;
    if (talked_to_pnj(game, 2) && game->adv == TALK_BRIDGEMAN)
        game->adv = TALK_NORTHGIRL;
    if (talked_to_pnj(game, 3) && game->adv == TALK_NORTHGIRL)
        game->adv = TALK_DAMOPIES;
    if (killed_wolves(game) && game->adv == TALK_DAMOPIES) {
        game->adv = KILL_WOLVES;
        del_pnj(game, 3);
    }
    if (talked_to_pnj(game, 4) && game->adv == KILL_WOLVES) {
        game->obj->bridge->repaired = true;
        game->adv = TALK_MINER;
        del_pnj(game, 1);
    }
    process_adv_second(game);
}
