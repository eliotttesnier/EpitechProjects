/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** interactions
*/

#include "rpg_header.h"

bool process_pnj_interaction(gamedata_t *game)
{
    pnj_t *pnj = interact_pnj(game);

    if (pnj == NULL)
        return (false);
    if (pnj->voicebox == NULL || pnj->unlocked == false)
        put_popup(game, "...");
    else {
        play_sfx(game, SFX_TALKING);
        put_popup(game, (pnj->voicebox != NULL ? pnj->voicebox->msg : "..."));
        pnj->talked = true;
        pnj->voicebox = pnj->voicebox->next;
    }
    return (true);
}

bool process_chest_interaction(gamedata_t *game)
{
    chest_t *chest = interact_chest(game);

    if (chest == NULL)
        return (false);
    if (chest->opened) {
        put_popup(game, "This chest is clearly opened ...");
        return (false);
    }
    if (is_inv_full(game)) {
        put_popup(game, "Your inventory is full !");
        return (false);
    }
    play_sfx(game, SFX_CHEST);
    chest->opened = true;
    chest->opening = true;
    sfClock_restart(chest->animation->clock);
    add_to_inv(game, chest->content);
    return (true);
}

void interact(gamedata_t *game)
{
    if (process_pnj_interaction(game))
        return;
    if (process_chest_interaction(game))
        return;
}
