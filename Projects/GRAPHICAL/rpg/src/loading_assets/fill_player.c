/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** fill_player
*/

#include "rpg_header.h"

static void fill_player_texture(gamedata_t *gamedata)
{
    gamedata->entity->player->sprite[0].texture = create_texture(
        "assets/sprites/player_movement/player(15x23).png");
    gamedata->entity->player->sprite[1].texture = create_texture(
        "assets/sprites/player_movement/player_sword(15x23).png");
    gamedata->entity->player->sprite[2].texture = create_texture(
        "assets/sprites/player_movement/player_spear(15x23).png");
    gamedata->entity->player->sprite[3].texture = create_texture(
        "assets/sprites/player_movement/player_axe(15x23).png");
    gamedata->entity->player->attack[0].texture = create_texture(
        "assets/sprites/player_attack/sword_attack(37x26).png");
    gamedata->entity->player->attack[1].texture = create_texture(
        "assets/sprites/player_attack/spear_attack(25x30).png");
    gamedata->entity->player->attack[2].texture = create_texture(
        "assets/sprites/player_attack/axe_attack(35x25).png");
}

static void fill_player_sprites(gamedata_t *gamedata)
{
    for (int i = 0; i < 4; i++) {
        gamedata->entity->player->sprite[i].rect = (sfIntRect){0, 0, 15, 23};
        gamedata->entity->player->sprite[i].sprite = sfSprite_create();
        sfSprite_setTexture(gamedata->entity->player->sprite[i].sprite,
            gamedata->entity->player->sprite[i].texture, sfFalse);
        sfSprite_setTextureRect(gamedata->entity->player->sprite[i].sprite,
            gamedata->entity->player->sprite[i].rect);
    }
    gamedata->entity->player->attack[0].rect = (sfIntRect){0, 0, 37, 26};
    gamedata->entity->player->attack[1].rect = (sfIntRect){0, 0, 25, 30};
    gamedata->entity->player->attack[2].rect = (sfIntRect){0, 0, 35, 25};
    for (int i = 0; i < 3; i++) {
        gamedata->entity->player->attack[i].sprite = sfSprite_create();
        sfSprite_setTexture(gamedata->entity->player->attack[i].sprite,
            gamedata->entity->player->attack[i].texture, sfFalse);
        sfSprite_setTextureRect(gamedata->entity->player->attack[i].sprite,
            gamedata->entity->player->attack[i].rect);
    }
}

static void fill_stats(gamedata_t *gamedata, config_t *config)
{
    gamedata->inventory->stats = malloc(sizeof(stats_t));
    gamedata->inventory->stats->attack = atoi(config->line[4]);
    gamedata->inventory->stats->defense = atoi(config->line[5]);
    gamedata->inventory->stats->health = atoi(config->line[3]);
    gamedata->inventory->stats->max_health = 100;
    gamedata->inventory->stats->mana = atoi(config->line[7]);
    gamedata->inventory->stats->xp = atoi(config->line[6]);
}

void fill_fight(gamedata_t *game)
{
    game->entity->player->fight = malloc(sizeof(fight_t) * 1);
    game->entity->player->fight->attacking = false;
    game->entity->player->fight->can_attack = true;
    game->entity->player->fight->buffer = sfClock_create();
    game->entity->player->fight->axe_hitbox = (sfIntRect){-10, -10, 20, 10};
    game->entity->player->fight->spear_hitbox = (sfIntRect){-5, -15, 10, 15};
    game->entity->player->fight->sword_hitbox = (sfIntRect){-10, -10, 20, 10};
}

void fill_player(gamedata_t *gamedata, config_t *config)
{
    gamedata->entity = malloc(sizeof(entity_t) * 1);
    gamedata->entity->player = malloc(sizeof(player_t) * 1);
    gamedata->entity->player->position =
        (sfVector2f){atoi(config->line[1]), atoi(config->line[2])};
    gamedata->entity->player->stat = malloc(sizeof(stats_t));
    gamedata->entity->player->stat->health = atoi(config->line[3]);
    gamedata->entity->player->stat->attack = atoi(config->line[4]);
    gamedata->entity->player->stat->defense = atoi(config->line[5]);
    gamedata->entity->player->stat->xp = atoi(config->line[6]);
    gamedata->entity->player->stat->mana = atoi(config->line[7]);
    gamedata->entity->player->animation = malloc(sizeof(animation_t));
    gamedata->entity->player->animation->clock = sfClock_create();
    gamedata->entity->player->movement = malloc(sizeof(movement_t));
    gamedata->entity->player->movement->clock = sfClock_create();
    gamedata->entity->player->movement->direction = (sfVector2f){0, 0};
    fill_player_texture(gamedata);
    fill_player_sprites(gamedata);
    fill_stats(gamedata, config);
    fill_fight(gamedata);
}
