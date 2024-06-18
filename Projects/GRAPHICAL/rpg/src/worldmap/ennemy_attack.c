/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** ennemy_attack
*/

#include "rpg_header.h"

void play_eny_sfx(gamedata_t *game, ennemy_t *eny)
{
    if (strcmp(eny->path, "assets/sprites/ennemy/giant_golem(96x96).png") == 0)
        play_sfx(game, SFX_GOLEM);
    if (strcmp(eny->path, "assets/sprites/ennemy/goblin(48x48).png") == 0)
        play_sfx(game, SFX_GOBELIN);
    if (strcmp(eny->path, "assets/sprites/ennemy/wolf(48x34).png") == 0)
        play_sfx(game, SFX_WOLF);
}

void check_eny_attack(gamedata_t *game, ennemy_t *eny)
{
    float seconds = sfClock_getElapsedTime(eny->fight->buffer).microseconds
    / 1000000.0;

    if (seconds > ATTACK_SPEED_ENY) {
        sfClock_restart(eny->fight->buffer);
        eny->fight->attacking = true;
    } else {
        eny->fight->attacking = false;
    }
    if (eny->fight->attacking == true) {
        play_sfx(game, SFX_DAMAGE);
        play_eny_sfx(game, eny);
        set_player_color(game, true);
        game->inventory->stats->health -=
            ((eny->atk - game->inventory->stats->defense) <=
            0 ? 1 : eny->atk - game->inventory->stats->defense);
    }
}

void ennemy_attack(gamedata_t *game)
{
    ennemy_t *eny = game->entity->ennemy;

    for (; eny != NULL; eny = eny->next) {
        if (!eny->alive)
            continue;
        if (!is_eny_visible(game, eny))
            continue;
        if (!is_in_eny_range(game, eny)) {
            sfClock_restart(eny->fight->buffer);
            continue;
        }
        check_eny_attack(game, eny);
    }
}
