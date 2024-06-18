/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** entity_display
*/

#include "rpg_header.h"

void game_display_pnj_back(gamedata_t *game)
{
    pnj_t *tmp = game->entity->pnj;

    for (; tmp != NULL; tmp = tmp->next) {
        if (!is_pnj_visible(game, tmp))
            continue;
        if (tmp->position.y + 5 <= game->entity->player->position.y) {
        sfSprite_setTextureRect(tmp->sprite->sprite, tmp->sprite->rect);
        sfRenderWindow_drawSprite(game->window->window,
            tmp->sprite->sprite, NULL);
        }
    }
}

void game_display_pnj_front(gamedata_t *game)
{
    pnj_t *tmp = game->entity->pnj;

    for (; tmp != NULL; tmp = tmp->next) {
        if (!is_pnj_visible(game, tmp))
            continue;
        if (tmp->position.y + 5 > game->entity->player->position.y) {
        sfSprite_setTextureRect(tmp->sprite->sprite, tmp->sprite->rect);
        sfRenderWindow_drawSprite(game->window->window,
            tmp->sprite->sprite, NULL);
        }
    }
}

void game_display_ennemy_back(gamedata_t *game)
{
    ennemy_t *tmp = game->entity->ennemy;

    for (; tmp != NULL; tmp = tmp->next) {
        if (!tmp->alive)
            continue;
        if (!is_eny_visible(game, tmp))
            continue;
        if (game->entity->player->position.y + 12 > tmp->position.y +
            (tmp->sprite->rect.height * 0.65)) {
        sfSprite_setTextureRect(tmp->sprite->sprite, tmp->sprite->rect);
        sfRenderWindow_drawSprite(game->window->window,
            tmp->sprite->sprite, NULL);
        }
    }
}

void game_display_ennemy_front(gamedata_t *game)
{
    ennemy_t *tmp = game->entity->ennemy;

    for (; tmp != NULL; tmp = tmp->next) {
        if (!tmp->alive)
            continue;
        if (!is_eny_visible(game, tmp))
            continue;
        if (game->entity->player->position.y + 12 <= tmp->position.y +
            (tmp->sprite->rect.height * 0.65)) {
        sfSprite_setTextureRect(tmp->sprite->sprite, tmp->sprite->rect);
        sfRenderWindow_drawSprite(game->window->window,
            tmp->sprite->sprite, NULL);
        }
    }
}

static int get_offset(ennemy_t *eny)
{
    if (strcmp(eny->path, "assets/sprites/ennemy/giant_golem(96x96).png") == 0)
        return (50);
    return (10);
}

static void display_lifebar(gamedata_t *game, ennemy_t *eny)
{
    sfVector2f center = get_center(eny->sprite);
    double percent = ((double)eny->hp / (double)eny->maxhp) * (double)100;

    center.y -= get_offset(eny);
    sfRectangleShape_setSize(eny->lifebar->life,
    (sfVector2f){(double)((double)50 * (percent / (double)100)), 5});
    sfRectangleShape_setPosition(eny->lifebar->back, center);
    sfRectangleShape_setPosition(eny->lifebar->life, center);
    sfRenderWindow_drawRectangleShape(game->window->window,
        eny->lifebar->back, NULL);
    sfRenderWindow_drawRectangleShape(game->window->window,
        eny->lifebar->life, NULL);
}

void display_ennemy_lifebar(gamedata_t *game)
{
    ennemy_t *eny = game->entity->ennemy;

    for (; eny != NULL; eny = eny->next) {
        if (!eny->alive)
            continue;
        if (!is_eny_visible(game, eny))
            continue;
        display_lifebar(game, eny);
    }
}
