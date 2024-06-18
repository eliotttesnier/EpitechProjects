/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** update_text
*/

#include "rpg_header.h"

void update_inventory_text(gamedata_t *game)
{
    game->inventory->atk =
        recreate_text(game->inventory->atk, "assets/fonts/main_font.ttf");
    game->inventory->def =
        recreate_text(game->inventory->def, "assets/fonts/main_font.ttf");
    game->inventory->hp =
        recreate_text(game->inventory->hp, "assets/fonts/main_font.ttf");
    game->inventory->mana =
        recreate_text(game->inventory->mana, "assets/fonts/main_font.ttf");
    game->inventory->xp =
        recreate_text(game->inventory->xp, "assets/fonts/main_font.ttf");
    game->inventory->atk->str = get_atk(game);
    game->inventory->def->str = get_def(game);
    game->inventory->hp->str = get_hp(game);
    game->inventory->mana->str = get_mana(game);
    game->inventory->xp->str = get_xp(game);
    sfText_setString(game->inventory->atk->text, game->inventory->atk->str);
    sfText_setString(game->inventory->def->text, game->inventory->def->str);
    sfText_setString(game->inventory->hp->text, game->inventory->hp->str);
    sfText_setString(game->inventory->mana->text, game->inventory->mana->str);
    sfText_setString(game->inventory->xp->text, game->inventory->xp->str);
}

void update_text(gamedata_t *game)
{
    game->hud->hp = recreate_text(game->hud->hp, "assets/fonts/main_font.ttf");
    game->hud->xp = recreate_text(game->hud->xp, "assets/fonts/main_font.ttf");
    game->hud->mana = recreate_text(game->hud->mana,
        "assets/fonts/main_font.ttf");
    game->hud->hp->str = get_hp(game);
    game->hud->xp->str = get_xp(game);
    game->hud->mana->str = get_mana(game);
    sfText_setString(game->hud->hp->text, game->hud->hp->str);
    sfText_setString(game->hud->xp->text, game->hud->xp->str);
    sfText_setString(game->hud->mana->text, game->hud->mana->str);
    update_inventory_text(game);
}
