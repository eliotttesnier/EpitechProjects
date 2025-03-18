/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** fill_hud
*/

#include "rpg_header.h"

void fill_map(gamedata_t *game)
{
    game->hud->minimap = malloc(sizeof(hud_map_t) * 1);
    game->hud->minimap->map = create_sprite("assets/HUD/map.png",
        (sfIntRect){0, 0, 100, 100});
    game->hud->minimap->player = create_sprite("assets/HUD/player.png",
        (sfIntRect){0, 0, 2, 2});
    game->hud->minimap->cadre = create_sprite("assets/HUD/cadre.png",
        (sfIntRect){0, 0, 101, 101});
}

void fill_popup(gamedata_t *game)
{
    game->hud->popup = malloc(sizeof(popup_t) * 1);
    game->hud->popup->msg = NULL;
    game->hud->popup->back = create_sprite("assets/HUD/popup.png",
        (sfIntRect){0, 0, 200, 75});
    sfSprite_setOrigin(game->hud->popup->back->sprite,
        (sfVector2f){100, 50});
    game->hud->popup->time_since_display = sfClock_create();
}

void fill_text_hud(gamedata_t *game)
{
    game->hud->hp = create_text("assets/fonts/main_font.ttf");
    game->hud->mana = create_text("assets/fonts/main_font.ttf");
    game->hud->xp = create_text("assets/fonts/main_font.ttf");
    game->hud->hp->str = get_hp(game);
    game->hud->mana->str = get_mana(game);
    game->hud->xp->str = get_xp(game);
    sfText_setString(game->hud->hp->text, game->hud->hp->str);
    sfText_setString(game->hud->mana->text, game->hud->mana->str);
    sfText_setString(game->hud->xp->text, game->hud->xp->str);
    sfText_scale(game->hud->hp->text, (sfVector2f){0.5, 0.5});
    sfText_scale(game->hud->mana->text, (sfVector2f){0.5, 0.5});
    sfText_scale(game->hud->xp->text, (sfVector2f){0.5, 0.5});
}

void fill_adv(gamedata_t *game, config_t *config)
{
    sfIntRect rect = {0, 0, 1920 / 4, 1080 / 4};
    config_t *adv = get_node("ADV", config);

    game->adv = atoi(adv->line[1]);
    game->hud->adv[0] = create_sprite("assets/adv/TALK_BEACHMAN.png", rect);
    game->hud->adv[1] = create_sprite("assets/adv/OPEN_CHEST.png", rect);
    game->hud->adv[2] = create_sprite("assets/adv/TALK_BRIDGEMAN.png", rect);
    game->hud->adv[3] = create_sprite("assets/adv/TALK_NORTHGIRL.png", rect);
    game->hud->adv[4] = create_sprite("assets/adv/TALK_DAMOPIES.png", rect);
    game->hud->adv[5] = create_sprite("assets/adv/KILL_WOLVES.png", rect);
    game->hud->adv[6] = create_sprite("assets/adv/TALK_MINER.png", rect);
    game->hud->adv[7] = create_sprite("assets/adv/KILL_GOLEM.png", rect);
    game->hud->adv[8] = create_sprite("assets/adv/ENTER_MINES.png", rect);
    game->hud->adv[9] = create_sprite("assets/adv/FIND_TWO_CHEST.png", rect);
    game->hud->adv[10] = create_sprite("assets/adv/KILL_TWO_GOLEMS.png", rect);
    game->hud->adv[11] = create_sprite("assets/adv/TALK_DAMOPIESAGAINWTF.png",
        rect);
    game->hud->adv[12] = create_sprite("assets/adv/END.png", rect);
}

static void fill_gameover(gamedata_t *game)
{
    game->hud->gameover = create_sprite("assets/HUD/gameover.png",
        (sfIntRect){0, 0, 1920 / 4, 1080 / 4});
}

void fill_game_hud(gamedata_t *game, config_t *config)
{
    (void)config;
    game->kill_count = 0;
    game->hud = malloc(sizeof(hud_t) * 1);
    fill_map(game);
    fill_text_hud(game);
    fill_popup(game);
    fill_adv(game, config);
    fill_gameover(game);
}
