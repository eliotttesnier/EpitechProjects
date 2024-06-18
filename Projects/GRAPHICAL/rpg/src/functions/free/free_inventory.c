/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** free_inventory
*/

#include "rpg_header.h"

void free_backpack(backpack_t *back)
{
    if (back == NULL)
        return;
    free_backpack(back->next);
    free_sprite(back->sprite);
    free(back);
}

void free_equip(equipment_t *equip)
{
    for (int i = 0; i < 5; i++) {
        if (equip->equiped[i] != NULL) {
            free_sprite(equip->sprites[i]);
        }
    }
    free(equip);
}

void free_preview(preview_t *pre)
{
    free_sprite_l(pre->not_worn[HELMET]);
    free_sprite_l(pre->worn[HELMET]);
    free_sprite_l(pre->not_worn[CHEST]);
    free_sprite_l(pre->worn[CHEST]);
    free_sprite_l(pre->not_worn[GLOVES]);
    free_sprite_l(pre->worn[GLOVES]);
    free_sprite_l(pre->not_worn[BOOTS]);
    free_sprite_l(pre->worn[BOOTS]);
    free(pre);
}

void free_inventory(inventory_t *inv)
{
    free_backpack(inv->backpack);
    free_sprite(inv->backsprite);
    free_equip(inv->equipment);
    free_sprite(inv->equipsprite);
    free_preview(inv->preview);
    free_text(inv->atk);
    free_text(inv->def);
    free_text(inv->hp);
    free_text(inv->mana);
}
