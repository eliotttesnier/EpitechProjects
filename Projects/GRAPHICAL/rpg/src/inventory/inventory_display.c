/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** inventory_display
*/

#include "rpg_header.h"

void display_backpack(gamedata_t *game)
{
    backpack_t *back = game->inventory->backpack;

    while (back != NULL) {
        sfRenderWindow_drawSprite(game->window->window,
            back->sprite->sprite, NULL);
        back = back->next;
    }
}

void display_equip(gamedata_t *game)
{
    equipment_t *equip = game->inventory->equipment;

    if (equip->equiped[HELMET] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            equip->sprites[HELMET]->sprite, NULL);
    if (equip->equiped[CHEST] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            equip->sprites[CHEST]->sprite, NULL);
    if (equip->equiped[GLOVES] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            equip->sprites[GLOVES]->sprite, NULL);
    if (equip->equiped[BOOTS] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            equip->sprites[BOOTS]->sprite, NULL);
    if (equip->equiped[WEAPON] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            equip->sprites[WEAPON]->sprite, NULL);
}

void display_preview(gamedata_t *game)
{
    sfRenderWindow_drawSprite(game->window->window,
        game->inventory->preview->not_worn[HELMET].sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->inventory->preview->not_worn[CHEST].sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->inventory->preview->not_worn[GLOVES].sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->inventory->preview->not_worn[BOOTS].sprite, NULL);
    if (game->inventory->equipment->equiped[HELMET] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            game->inventory->preview->worn[HELMET].sprite, NULL);
    if (game->inventory->equipment->equiped[CHEST] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            game->inventory->preview->worn[CHEST].sprite, NULL);
    if (game->inventory->equipment->equiped[GLOVES] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            game->inventory->preview->worn[GLOVES].sprite, NULL);
    if (game->inventory->equipment->equiped[BOOTS] != NULL)
        sfRenderWindow_drawSprite(game->window->window,
            game->inventory->preview->worn[BOOTS].sprite, NULL);
}

static void display_hang(gamedata_t *game)
{
    if (game->inventory->hanging == NULL)
        return;
    sfRenderWindow_drawSprite(game->window->window,
        game->inventory->hanging->sprite->sprite, NULL);
}

static void display_stats(gamedata_t *game)
{
    sfText_scale(game->inventory->xp->text, (sfVector2f){0.35, 0.35});
    sfText_scale(game->inventory->mana->text, (sfVector2f){0.35, 0.35});
    sfText_scale(game->inventory->hp->text, (sfVector2f){0.35, 0.35});
    sfText_scale(game->inventory->atk->text, (sfVector2f){0.35, 0.35});
    sfText_scale(game->inventory->def->text, (sfVector2f){0.35, 0.35});
    sfRenderWindow_drawText(game->window->window,
        game->inventory->xp->text, NULL);
    sfRenderWindow_drawText(game->window->window,
        game->inventory->hp->text, NULL);
    sfRenderWindow_drawText(game->window->window,
        game->inventory->atk->text, NULL);
    sfRenderWindow_drawText(game->window->window,
        game->inventory->mana->text, NULL);
    sfRenderWindow_drawText(game->window->window,
        game->inventory->def->text, NULL);
}

void inventory_display(gamedata_t *game)
{
    sfRenderWindow_drawSprite(game->window->window,
        game->inventory->backsprite->sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->inventory->skillsprite->sprite, NULL);
    sfRenderWindow_drawSprite(game->window->window,
        game->inventory->equipsprite->sprite, NULL);
    display_backpack(game);
    display_equip(game);
    display_preview(game);
    display_hang(game);
    display_stats(game);
    sfRenderWindow_display(game->window->window);
}
