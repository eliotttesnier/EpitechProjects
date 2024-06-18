/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** fill_preview
*/

#include "rpg_header.h"

void preview_scale(gamedata_t *game)
{
    for (int i = 0; i < 4; i++) {
        sfSprite_setScale(game->inventory->preview->worn[i].sprite,
            (sfVector2f){0.25, 0.25});
        sfSprite_setScale(game->inventory->preview->not_worn[i].sprite,
            (sfVector2f){0.25, 0.25});
    }
}

void fill_hud(gamedata_t *game)
{
    game->inventory->atk = create_text("assets/fonts/main_font.ttf");
    game->inventory->hp = create_text("assets/fonts/main_font.ttf");
    game->inventory->mana = create_text("assets/fonts/main_font.ttf");
    game->inventory->def = create_text("assets/fonts/main_font.ttf");
    game->inventory->xp = create_text("assets/fonts/main_font.ttf");
    game->inventory->atk->str = get_atk(game);
    game->inventory->def->str = get_def(game);
    game->inventory->mana->str = get_mana(game);
    game->inventory->hp->str = get_hp(game);
    game->inventory->xp->str = get_xp(game);
    sfText_setString(game->inventory->atk->text, game->inventory->atk->str);
    sfText_setString(game->inventory->def->text, game->inventory->def->str);
    sfText_setString(game->inventory->mana->text, game->inventory->mana->str);
    sfText_setString(game->inventory->hp->text, game->inventory->hp->str);
    sfText_setString(game->inventory->xp->text, game->inventory->xp->str);
    sfText_scale(game->inventory->xp->text, (sfVector2f){0.35, 0.35});
    sfText_scale(game->inventory->mana->text, (sfVector2f){0.35, 0.35});
    sfText_scale(game->inventory->hp->text, (sfVector2f){0.35, 0.35});
    sfText_scale(game->inventory->atk->text, (sfVector2f){0.35, 0.35});
    sfText_scale(game->inventory->def->text, (sfVector2f){0.35, 0.35});
}

void fill_preview(gamedata_t *gamedata, config_t *config)
{
    (void)config;
    gamedata->inventory->preview = malloc(sizeof(preview_t));
    gamedata->inventory->preview->not_worn[HELMET] = *create_sprite(
        "assets/sprites/head_1(195x285).png", (sfIntRect){0, 0, 195, 285});
    gamedata->inventory->preview->not_worn[GLOVES] = *create_sprite(
        "assets/sprites/gloves_1(195x285).png", (sfIntRect){0, 0, 195, 285});
    gamedata->inventory->preview->not_worn[CHEST] = *create_sprite(
        "assets/sprites/chest_1(195x285).png", (sfIntRect){0, 0, 195, 285});
    gamedata->inventory->preview->not_worn[BOOTS] = *create_sprite(
        "assets/sprites/boots_1(195x285).png", (sfIntRect){0, 0, 195, 285});
    gamedata->inventory->preview->worn[HELMET] = *create_sprite(
        "assets/sprites/head_2(195x285).png", (sfIntRect){0, 0, 195, 285});
    gamedata->inventory->preview->worn[GLOVES] = *create_sprite(
        "assets/sprites/gloves_2(195x285).png", (sfIntRect){0, 0, 195, 285});
    gamedata->inventory->preview->worn[CHEST] = *create_sprite(
        "assets/sprites/chest_2(195x285).png", (sfIntRect){0, 0, 195, 285});
    gamedata->inventory->preview->worn[BOOTS] = *create_sprite(
        "assets/sprites/boots_2(195x285).png", (sfIntRect){0, 0, 195, 285});
    preview_scale(gamedata);
    fill_hud(gamedata);
}
