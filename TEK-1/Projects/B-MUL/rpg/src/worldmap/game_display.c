/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** game_display
*/

#include "rpg_header.h"

int game_get_weapon_rect(gamedata_t *game)
{
    int id = 0;

    if (game->inventory->equipment->equiped[WEAPON] == NULL)
        return (0);
    id = game->inventory->equipment->equiped[WEAPON]->id;
    if (id >= 0 && id <= 4)
        return (1);
    if (id >= 5 && id <= 9)
        return (2);
    return (3);
}

static void void_game_display_attack(gamedata_t *game, int x)
{
    player_t *p = game->entity->player;
    sprite_t s = p->attack[x - 1];
    sfVector2f off = (sfVector2f){0, 2};

    if (x == 1 || x == 3)
        off.x = -10;
    if (x == 2)
        off.x = -5;
    sfSprite_setTextureRect(p->attack[x - 1].sprite, p->attack[x - 1].rect);
    sfSprite_move(s.sprite, off);
    sfRenderWindow_drawSprite(game->window->window,
        p->attack[x - 1].sprite, NULL);
    sfSprite_move(s.sprite, (sfVector2f){-off.x, -off.y});
}

void game_display_player(gamedata_t *game)
{
    player_t *p = game->entity->player;
    int x = game_get_weapon_rect(game);

    set_player_color(game, false);
    if (game->entity->player->fight->attacking && x != 0) {
        void_game_display_attack(game, x);
        return;
    }
    sfSprite_setTextureRect(p->sprite[x].sprite, p->sprite[x].rect);
    sfRenderWindow_drawSprite(game->window->window, p->sprite[x].sprite, NULL);
}

static void display_bridge(gamedata_t *game)
{
    if (game->obj->bridge->repaired)
        sfRenderWindow_drawSprite(game->window->window,
            game->obj->bridge->fixed->sprite, NULL);
    else
        sfRenderWindow_drawSprite(game->window->window,
            game->obj->bridge->broken->sprite, NULL);
    if (game->adv < KILL_GOLEM)
        sfRenderWindow_drawSprite(game->window->window,
            game->obj->gate->sprite, NULL);
}

void game_display(gamedata_t *game, bool inventory)
{
    sfRenderWindow_clear(game->window->window, sfBlack);
    sfRenderWindow_drawSprite(game->window->window,
        game->map->back->sprite, NULL);
    display_bridge(game);
    game_display_pnj_back(game);
    game_display_ennemy_back(game);
    display_objects_back(game);
    game_display_player(game);
    game_display_pnj_front(game);
    game_display_ennemy_front(game);
    display_ennemy_lifebar(game);
    display_objects_front(game);
    sfRenderWindow_drawSprite(game->window->window,
        game->map->dec->sprite, NULL);
    if (!inventory) {
        display_hud(game);
        sfRenderWindow_display(game->window->window);
    }
}
