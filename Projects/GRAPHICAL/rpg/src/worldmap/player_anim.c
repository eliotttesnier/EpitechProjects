/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** player_anim
*/

#include "rpg_header.h"

static void actualise_attack_rect(player_t *player, float time, sfClock *clock)
{
    if (time < 150000)
        return;
    sfClock_restart(clock);
    for (int i = 0; i < 3; i++) {
        player->attack[i].rect.left += player->attack[i].rect.width;
        if (player->attack[i].rect.left == player->attack[i].rect.width * 4) {
            player->attack[i].rect.left = 0;
            player->fight->attacking = false;
        }
    }
}

static void actualise_rect_dir_attack(player_t *p)
{
    for (int i = 0; i < 3; i++) {
        p->attack[i].rect.top = 0;
        if (p->movement->direction.x == 0 && p->movement->direction.y > 0)
            p->attack[i].rect.top = p->attack[i].rect.height * 0;
        if (p->movement->direction.x > 0)
            p->attack[i].rect.top = p->attack[i].rect.height * 1;
        if (p->movement->direction.x < 0)
            p->attack[i].rect.top = p->attack[i].rect.height * 3;
        if (p->movement->direction.x == 0 && p->movement->direction.y < 0)
            p->attack[i].rect.top = p->attack[i].rect.height * 2;
    }
}

void actualise_rect(player_t *player)
{
    for (int i = 0; i < 4; i++) {
        player->sprite[i].rect.left += player->sprite[i].rect.width;
        if (player->sprite[i].rect.left == player->sprite[i].rect.width * 6)
            player->sprite[i].rect.left = 0;
    }
}

void actualise_rect_dir(player_t *p)
{
    for (int i = 0; i < 4; i++) {
        p->sprite[i].rect.top = 23 * 0;
        if (p->movement->direction.x == 0 && p->movement->direction.y > 0)
            p->sprite[i].rect.top = 23 * 1;
        if (p->movement->direction.x > 0)
            p->sprite[i].rect.top = 23 * 2;
        if (p->movement->direction.x < 0)
            p->sprite[i].rect.top = 23 * 3;
        if (p->movement->direction.x == 0 && p->movement->direction.y < 0)
            p->sprite[i].rect.top = 23 * 4;
    }
}

void player_anim(player_t *player)
{
    float time = sfClock_getElapsedTime(player->animation->clock).microseconds;

    if (time > 100000) {
        if (player->fight->attacking)
            actualise_attack_rect(player, time, player->animation->clock);
        else {
            actualise_rect(player);
            sfClock_restart(player->animation->clock);
        }
    }
    if (player->fight->attacking)
        actualise_rect_dir_attack(player);
    else
        actualise_rect_dir(player);
}
